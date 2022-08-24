/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piboidin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 23:17:29 by piboidin          #+#    #+#             */
/*   Updated: 2022/08/24 23:18:32 by piboidin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

pthread_mutex_t	*ft_init_l_fork(int i, int nb_ph, pthread_mutex_t *mut)
{
	(void)nb_ph;
	if (i == 0)
		return (&mut[i]);
	else
		return (&mut[i - 1]);
}

pthread_mutex_t	*ft_init_r_fork(int i, int nb_ph, pthread_mutex_t *mut)
{
	if (i == 0)
		return (&mut[nb_ph - 1]);
	else
		return (&mut[i]);
}

void	ft_init_ph(t_info *info, t_philo *philo, long begin_v, int i)
{
	philo->id = i + 1;
	philo->last_eat = 0;
	pthread_mutex_init(&(philo->mut_last_eat), 0);
	philo->num_of_eat = 0;
	philo->quota = 0;
	philo->begin_val = begin_v;
	philo->log = &info->log;
	philo->left_fork = 0;
	philo->right_fork = 0;
	philo->l_fork = ft_init_l_fork(i, info->ph_const.nb_ph, info->all_fork);
	philo->r_fork = ft_init_r_fork(i, info->ph_const.nb_ph, info->all_fork);
	philo->ph_const = &info->ph_const;
	philo->end = &(info->end);
	philo->t_endhreads = &(info->t_endhreads);
	philo->setup = &(info->setup);
}
