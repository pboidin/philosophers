/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piboidin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 23:20:03 by piboidin          #+#    #+#             */
/*   Updated: 2022/08/24 23:20:50 by piboidin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_init_const(int argc, char **argv, t_const *ph_const)
{
	if (argc == 4)
		ph_const->nb_rep = -1;
	else
	{
		ph_const->nb_rep = ft_atoi(argv[argc - 1]);
		if (ph_const->nb_rep == -1)
			return (3);
	}
	ph_const->nb_ph = ft_atoi(argv[0]);
	ph_const->time_to_die = ft_atoi(argv[1]);
	ph_const->time_to_eat = ft_atoi(argv[2]);
	ph_const->time_to_sleep = ft_atoi(argv[3]);
	if (ph_const->nb_ph < 1 || ph_const->time_to_die < 1
		|| ph_const->time_to_eat < 1 || ph_const->time_to_sleep < 1)
		return (3);
	return (0);
}
