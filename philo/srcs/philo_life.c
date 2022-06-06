#include "philo.h"

void    ft_printer(t_info *master, char *str, int i)
{
	pthread_mutex_lock(&master->act_m);
	if (!(master->dead))
 	{
 		printf("(%lli)\t ", ft_runtime_to_ms() - master->birth_time);
 		printf("philo %i ", i + 1);
 		printf("%s\n", str);
 	}
 	pthread_mutex_unlock(&master->act_m);
 	return ;
}

void	*ft_philo_life(void *void_p)
{
	t_philo	*philo;
	t_info	*master;

	philo = (struct s_philo *)void_p;
	master = philo->master;
	if (philo->id % 2)
		usleep(2000);
	while (!(master->dead))
	{
		ft_eat(philo);
		if (master->all_eat)
			break;
		ft_printer(master, "is sleeping", philo->id);
		ft_sleep(master->time_to_sleep, master);
		ft_printer(master, "is thinking", philo->id);
	}
	return (NULL);
}

void	ft_health_center(t_info *master, t_philo *philo)
{
	int	i;

	while (!(master->all_eat))
	{
		i = 0;
		while (i++ < master->nb_ph && !(master->dead))
		{
			pthread_mutex_lock(&master->eat_m);
			if ((ft_runtime_to_ms() - philo[i].time_eat) > master->time_to_die)
			{
				ft_printer(master, "died", i);
				master->dead = 1;
			}
			pthread_mutex_unlock(&master->eat_m);
			usleep(1000);
		}
		if (master->dead)
			break ;
		i = 0;
		while ((master->nb_eat != -1) && (i < master->nb_ph)
				&& (philo[i].eat >= master->nb_eat))
				i++;
		if (i == master->nb_ph)
			master->all_eat = 1;
	}
}

void	ft_remove(t_info *master, t_philo *philo)
{
	int	i;

	i = 0;
	while (i++ < master->nb_ph)
		pthread_join(philo[i].thread_p, NULL);
	i = 0;
	while (i++ < master->nb_ph)
		pthread_mutex_destroy(&master->for_m[i]);
	pthread_mutex_destroy(&master->act_m);
}

int		ft_life_creator(t_info *master)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = master->philo;
	master->birth_time = ft_runtime_to_ms();
	while (i < master->nb_ph)
	{
		if (pthread_create(&philo[i].thread_p, NULL, &ft_philo_life, &philo[i]))
			return (1);
		philo[i].time_eat = ft_runtime_to_ms();
		i++;
	}
	ft_health_center(master, master->philo);
	ft_remove(master, philo);
	return (0);
}

/* ************************************************************************** */
/* Now that we parsed everything, and our structs are filled, we create a     */
/* thread for each different philosophers and sends them the routine          */
/* We initialize our timestamp at the moment the thread is created.           */
/* At the end of the loop, we check if any philosopher is dead, then we       */
/* destroy all the threads created to avoid leaks and such.                   */
/* ************************************************************************** */
