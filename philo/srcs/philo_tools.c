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

long long	ft_runtime_to_ms(void)
{
	long long		ms;
	struct timeval	time;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000;
	ms += time.tv_usec / 1000;
	return (ms);
}

void	ft_nbr_one(t_philo *philo)
{
	t_info	*master;

	master = philo->master;
	ft_printer(master, philo->id, "has taken a fork");
	ft_sleep(master->time_to_die, master);
	ft_health_check(master, master->philo);
}

void	ft_eat(t_philo *philo)
{
	t_info	*master;

	master = philo->master;
	if (master->nb_ph == 1)
		ft_nbr_one(philo);
	else
	{
		pthread_mutex_lock(&master->for_m[philo->left]);
		ft_printer(master, philo->id, "has taken a fork");
		pthread_mutex_lock(&master->for_m[philo->right]);
		ft_printer(master, philo->id, "has taken a fork");
		pthread_mutex_lock(&master->eat_m);
		ft_printer(master, philo->id, "is eating");
		philo->eat_time = ft_runtime_to_ms();
		pthread_mutex_unlock(&master->eat_m);
		ft_sleep(master->time_to_eat, master);
		(philo->eat)++;
		pthread_mutex_unlock(&master->for_m[philo->left]);
		pthread_mutex_unlock(&master->for_m[philo->right]);
	}
}

void	ft_sleep(long long time, t_info *master)
{
	long long	i;

	i = ft_runtime_to_ms();
	while (!(master->dead))
	{
		if ((ft_runtime_to_ms() - i) >= time)
			break ;
		usleep(50);
	}
}
