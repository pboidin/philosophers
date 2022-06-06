#include "philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	nb;
	int	tmp;

	i = 0;
	nb = 0;
	tmp = 0;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (str[i] - '0') + (nb * 10);
		i++;
		if (nb < tmp)
			return (0);
		tmp = nb;
	}
	if (str[i] != 0)
		return (0);
	return (nb);
}

long long int	ft_runtime_to_ms(void)
{
	unsigned long long int			ms;
	static unsigned long long int	start;
	static struct timeval			time;

	start = 0;
	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000;
	ms += time.tv_usec / 1000;
	if (!start)
		start = ms;
	return (ms - start);
}

void	ft_nbr_one(t_philo *philo)
{
	t_info	*master;

	master = philo->master;
	ft_printer(master, "has token a fork", philo->id);
	ft_sleep(master->time_to_die, master);
	ft_health_center(master, master->philo);
}	

void	ft_eat(t_philo *philo)
{
	t_info	*master;

	master = t_philo->master;
	if (master->nb_ph == 1)
		ft_nbr_one(philo);
	else
	{
		pthread_mutex_lock(&master->for_m[philo->left]);
		ft_printer(master, "has token a fork", philo->id);
		pthread_mutex_lock(&master->for_m[philo->right]);
		ft_printer(master, "has token a fork", philo->id);
		pthread_mutex_lock(&master->eat_m);
		ft_printer(master, "is eating", philo->id);
		philo->time_eat = ft_runtime_to_ms();
		pthread_mutex_unlock(&master->eat_m);
		ft_sleep(master->time_to_eat, master);
		(philo->eat)++;
		pthread_mutex_unlock(&master->for_m[philo->left]);
		pthread_mutex_unlock(&master->for_m[philo->right]);
	}
}

void	ft_sleep(long long time, t_info *master)
{
	long long	t;

	t = ft_runtime_to_ms();
	while (!(master->dead))
	{
		if ((ft_runtime_to_ms() - t) >= time)
			break;
		usleep(50);
	}
}
