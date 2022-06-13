#include "philo.h"

int	ft_init_philo(t_info *master)
{
	int	i;

	i = master->nb_ph;
	while (--i >= 0)
	{
		master->philo[i].id = i;
		master->philo[i].eat = 0;
		master->philo[i].left = i;
		master->philo[i].right = (i + 1) % master->nb_ph;
		master->philo[i].eat_time = 0;
		master->philo[i].master = master;
	}
	return (true);
}

/* ************************************************************************** */
/* initialize all our master in our master structure.                         */
/* ************************************************************************** */

int	ft_init_mutex(t_info *master)
{
	int	i;

	i = master->nb_ph;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&master->for_m[i], NULL) != 0)
			return (false);
	}
	if (pthread_mutex_init(&master->act_m, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&master->eat_m, NULL) != 0)
		return (false);
	return (true);
}

/* ************************************************************************** */
/* the parse_mutex function that initializes all the mutexes in our structs   */
/* so we can use them after in our philo_actions functions                    */
/* ************************************************************************** */

int	ft_creation_process(t_info *master, char **argv)
{
	master->nb_ph = ft_atoi(argv[1]);
	master->time_to_die = ft_atoi(argv[2]);
	master->time_to_eat = ft_atoi(argv[3]);
	master->time_to_sleep = ft_atoi(argv[4]);
	master->dead = 0;
	master->all_eat = 0;
	if (master->nb_ph < 1 || master->time_to_die < 1 || master->time_to_eat < 0
		|| master->time_to_sleep < 0 || master->nb_ph > MAX_PHILO)
		return (false);
	if (argv[5])
	{
		master->nb_eat = ft_atoi(argv[5]);
		if (master->nb_eat <= 0)
			return (false);
	}
	else
		master->nb_eat = -1;
	if (!ft_init_mutex(master))
		return (false);
	if (!ft_init_philo(master))
		return (false);
	return (true);
}

/* ************************************************************************** */
/* parse all fills our structs with our program parameters at first           */
/* with our 2 structures, master and philos which contains all the informations */
/* Basically we just initialize mutexes and structures                        */
/* ************************************************************************** */
