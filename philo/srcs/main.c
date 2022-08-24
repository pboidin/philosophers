/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piboidin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 23:12:45 by piboidin          #+#    #+#             */
/*   Updated: 2022/08/24 23:14:45 by piboidin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	ft_check_last_eat(t_info *info, int *stop, int i, int die)
{
	pthread_mutex_lock(&(info->philos[i].mut_last_eat));
	if (timestamp(info->begin) - info->philos[i].last_eat >= (long)die)
	{
		pthread_mutex_lock(&(info->end.mutex));
		info->end.end = 1;
		pthread_mutex_unlock(&(info->end.mutex));
		pthread_mutex_lock(&info->log);
		printf("%li %d %s\n", timestamp(info->begin),
			info->philos[i].id, "died");
		pthread_mutex_unlock(&info->log);
		*stop = 1;
	}
	pthread_mutex_unlock(&(info->philos[i].mut_last_eat));
}

static void	ft_dead_checker(t_info *info, int die, int nb_ph)
{
	int	i;
	int	stop;

	i = -1;
	pthread_mutex_lock(&(info->end.mutex));
	stop = info->end.end;
	pthread_mutex_unlock(&(info->end.mutex));
	if (stop)
		return ;
	while (++i < nb_ph)
	{
		ft_check_last_eat(info, &stop, i, die);
		if (stop)
			break ;
	}
	msleep(1, timestamp(0));
}

static int	ft_check_end(t_info *info)
{
	pthread_mutex_lock(&(info->end.mutex));
	pthread_mutex_lock(&info->t_endhreads.mutex);
	if (info->t_endhreads.end == info->ph_const.nb_ph
		|| info->end.end == 1 || info->ph_const.nb_rep == 0)
	{
		info->end.end = 1;
		return (pthread_mutex_unlock(&(info->t_endhreads.mutex)),
			pthread_mutex_unlock(&(info->end.mutex)), 0);
	}
	return (pthread_mutex_unlock(&(info->t_endhreads.mutex)),
		pthread_mutex_unlock(&(info->end.mutex)), 1);
}

int	main(int argc, char **argv)
{
	t_info	info;
	int		key;

	key = ft_check_args(argc, argv, &info.ph_const);
	if (key)
		return (ft_printer_error(key), 1);
	key = ft_init_info(&info, info.ph_const.nb_ph);
	if (key)
		return (ft_printer_error(key), 1);
	key = ft_init_threads(info.all_threads, info.philos, info.ph_const.nb_ph);
	if (key)
		return (ft_printer_thread_error(&info, key));
	while (timestamp(info.begin) < START)
		usleep(300);
	info.begin += START;
	while (ft_check_end(&info))
		ft_dead_checker(&info, info.ph_const.time_to_die,
			info.ph_const.nb_ph);
	key = ft_waiting_threads(&info);
	if (key)
		return (ft_free_table(&info), ft_printer_error(key), 1);
	ft_free_table(&info);
	return (0);
}
