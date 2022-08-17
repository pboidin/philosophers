#include "../includes/philosophers.h"

int	ft_thread(t_info *master)
{
	int			i;
	pthread_t	th_checker;

	i = -1;
	while (++i < master->nb_ph)
	{
		if (pthread_create(&master->philos[i].thread, NULL,
				ft_routine, (void *)&master->philos[i]))
			return (1);
		if (pthread_create(&th_checker, NULL,
				ft_check_routine, (void *)&master->philos[i]))
			return (1);
		pthread_detach(th_checker);
	}
	if (master->must_eat > 0)
	{
		if (pthread_create(&th_checker, NULL,
				ft_check_eat, (void *)master))
			return (1);
		pthread_detach(th_checker);
	}
	i = 0;
	while (i < master->nb_ph)
		pthread_join(master->philos[i++].thread, NULL);
	return (0);
}

void	ft_free_ph(t_info *master)
{
	int	i;

	i = 0;
	if (master->forks)
	{
		while (i < master->nb_ph)
		{
			pthread_mutex_destroy(&master->forks[i]);
			master->philos->l_fork = NULL;
			master->philos->r_fork = NULL;
			i++;
		}
	}
	pthread_mutex_destroy(&master->print_mutex);
	pthread_mutex_destroy(&master->die_mutex);
	pthread_mutex_destroy(&master->check_mutex);
	pthread_mutex_destroy(&master->last_eat_mutex);
	pthread_mutex_destroy(&master->eat_mutex);
	free(master->forks);
	if (master->philos)
		free(master->philos);
}

int	ft_create_master(t_info *master)
{
	int	i;

	master->is_dead = 0;
	i = -1;
	while (++i < master->nb_ph)
	{
		master->philos[i].id = i + 1;
		if (pthread_mutex_init(&master->forks[i], NULL))
			return (ft_error("Error\n"));
		if (i == 0)
			master->philos[i].l_fork = &master->forks[master->nb_ph - 1];
		else
			master->philos[i].l_fork = &master->forks[i - 1];
		master->philos[i].r_fork = &master->forks[i];
		master->philos[i].info = master;
		master->philos[i].num_of_eat = 0;
	}
	return (0);
}

int	ft_malloc_philo(t_info *master)
{
	master->philos = malloc(sizeof(t_philo) * master->nb_ph);
	master->forks = malloc(sizeof(pthread_mutex_t) * master->nb_ph);
	if (!(master->philos) || !(master->forks))
		return (1);
	if (pthread_mutex_init(&master->print_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&master->die_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&master->check_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&master->last_eat_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&master->eat_mutex, NULL))
		return (1);
	return (0);
}

int	ft_create_philo(t_info *master)
{
	if (ft_malloc_philo(master))
		return (1);
	if (ft_create_master(master))
		return (1);
	return (0);
}
