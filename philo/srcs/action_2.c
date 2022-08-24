/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piboidin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 23:10:53 by piboidin          #+#    #+#             */
/*   Updated: 2022/08/24 23:11:01 by piboidin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_sleep(t_philo *ph)
{
	int	i;

	i = ph->ph_const->time_to_sleep;
	ft_printer(ph, ph->id, ph->begin_val, "is sleeping");
	msleep(i, timestamp(0));
}

void	ft_eat(t_philo *ph)
{
	int	i;

	i = ph->ph_const->time_to_eat;
	ft_printer(ph, ph->id, ph->begin_val, "is eating");
	msleep(i, timestamp(0));
	ph->left_fork = 0;
	ph->right_fork = 0;
	pthread_mutex_unlock(ph->l_fork);
	pthread_mutex_unlock(ph->r_fork);
	ph->num_of_eat++;
}

long	ft_last_ph(t_philo *ph)
{
	if (ph->ph_const->time_to_eat < ph->ph_const->time_to_sleep)
		return (0);
	else
		return (ph->ph_const->time_to_eat - ph->ph_const->time_to_sleep + 10);
}

void	*ft_end(t_philo *ph)
{
	if (ph->left_fork)
	{
		pthread_mutex_unlock(ph->l_fork);
		ph->left_fork = 0;
	}
	if (ph->right_fork)
	{
		pthread_mutex_unlock(ph->r_fork);
		ph->right_fork = 0;
	}
	return (0);
}

void	*ft_routine(void *args)
{
	t_philo	*ph;

	ph = (t_philo *)args;
	ft_wait(ph);
	if (ft_rout_loop(ph))
		ft_printer(ph, ph->id, ph->begin_val, "is thinking");
	if (ph->id % 2 == 1)
		msleep(ph->ph_const->time_to_eat, timestamp(0));
	while (ft_rout_loop(ph))
	{
		if (ph->id % 2 == 1 && ph->id == ph->ph_const->nb_ph)
			msleep(ft_last_ph(ph), timestamp(0));
		if (ft_rout_loop(ph))
			ft_take_left_fork(ph);
		if (ft_rout_loop(ph))
			ft_take_right_fork(ph);
		if (ft_rout_loop(ph))
			ft_eat(ph);
		if (ft_rout_loop(ph))
			ft_sleep(ph);
		if (ft_rout_loop(ph))
			ft_printer(ph, ph->id, ph->begin_val, "is thinking");
	}
	return (ft_end(ph));
}
