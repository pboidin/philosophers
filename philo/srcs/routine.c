#include "../includes/philosophers.h"

int	ft_dead_checker(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&philo->info->check_mutex);
	if (philo->info->is_dead)
	{
		pthread_mutex_unlock(&philo->info->check_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->check_mutex);
	pthread_mutex_lock(&philo->info->last_eat_mutex);
	time = ft_runtime_to_ms() - philo->last_eat;
	pthread_mutex_unlock(&philo->info->last_eat_mutex);
	if (time > (long long) philo->info->time_to_die)
		return (0);
	return (1);
}

void	*ft_check_routine(void *info)
{
	t_philo		*philo;
	int			dead;

	philo = (t_philo *)info;
	dead = 0;
	usleep(100);
	while (!dead)
	{
		pthread_mutex_lock(&philo->info->die_mutex);
		if (!ft_dead_checker(philo) && philo->info->nb_ph > 1)
		{
			ft_dead_msg(philo, "is dead");
			pthread_mutex_lock(&philo->info->check_mutex);
			philo->info->is_dead = 1;
			pthread_mutex_unlock(&philo->info->check_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->info->die_mutex);
		pthread_mutex_lock(&philo->info->check_mutex);
		if (philo->info->is_dead)
			dead = 1;
		pthread_mutex_unlock(&philo->info->check_mutex);
		usleep(1000);
	}
	return (NULL);
}

int	ft_check_must_eat(t_info *master)
{
	int	i;
	int	must_eat;

	must_eat = master->must_eat;
	i = 0;
	while (i < master->nb_ph)
	{
		pthread_mutex_lock(&master->eat_mutex);
		if (master->philos[i].num_of_eat < must_eat)
		{
			pthread_mutex_unlock(&master->eat_mutex);
			return (1);
		}
		pthread_mutex_unlock(&master->eat_mutex);
		i++;
	}
	return (0);
}

void	*ft_check_eat(void *p)
{
	t_info	*info;
	int		dead;

	info = (t_info *) p;
	dead = 0;
	while (!dead)
	{
		if (!ft_check_must_eat(info))
		{
			pthread_mutex_lock(&info->check_mutex);
			info->is_dead = 1;
			if (info->is_dead)
				dead = 1;
			pthread_mutex_unlock(&info->check_mutex);
			return (NULL);
		}
		usleep(10);
	}
	return (NULL);
}

void	*ft_routine(void *info)
{
	t_philo	*philo;
	int		dead;

	dead = 0;
	philo = (t_philo *)info;
	if (philo->info->nb_ph == 1)
	{
		ft_one_philo(philo);
		return (NULL);
	}
	pthread_mutex_lock(&philo->info->last_eat_mutex);
	philo->last_eat = ft_runtime_to_ms();
	pthread_mutex_unlock(&philo->info->last_eat_mutex);
	if (philo->id % 2 == 0)
		usleep(200);
	while (!dead)
	{
		ft_forks(philo);
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
		dead = ft_check_death(philo);
		usleep(100);
	}
	return (NULL);
}
