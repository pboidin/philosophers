#include "philo.h"

int	init_philo(t_info *master)
{
	int	i;

	i = 0;
	while (i <= master->nb_ph)
	{
		master->philo[i].id = i;
		master->philo[i].eat = 0;
		master->philo[i].left = i;
		master->philo[i].right = (i + 1) % master->nb_ph;
		master->philo[i].time_eat = 0;
		master->philo[i].master = master;
	}
	return (0);
}

int	init_mutex(t_info *master)
{
	int	i;

	i = 0;
	while (i <= master->nb_ph)
	{
		if (pthread_mutex_init(&master->for_m[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&master->act_m, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&master->eat_m, NULL) != 0)
		return (1);
	return (0);
}

int	creation_process(t_info	*master, char **argv)
{
	master->nb_ph = ft_atoi(argv[1]);
	master->time_to_die = ft_atoi(argv[2]);
	master->time_to_eat = ft_atoi(argv[3]);
	master->time_to_sleep = ft_atoi(argv[4]);
	master->nb_eat = -1;
	master->dead = 0;
	master->all_eat = 0;
	if (argv[5])
	{
		master->nb_eat = ft_atoi(argv[5]);
		if (master->nb_eat <= 0)
			return (1);
	}
	if (master->nb_ph < 1 || master->time_to_die < 1 || master->time_to_eat < 0
			|| master->time_to_sleep < 0 || master->nb_ph > PHILO_MAX)
			return (1);
	if (!(init_mutex(master)))
		return (1);
	if (!(init_philo(master)))
		return (1);
	return (0);
}
