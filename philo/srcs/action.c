#include "../includes/philosophers.h"

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->last_eat_mutex);
	philo->last_eat = ft_runtime_to_ms();
	pthread_mutex_unlock(&philo->info->last_eat_mutex);
	ft_printer(philo, "is eating");
	pthread_mutex_lock(&philo->info->eat_mutex);
	philo->num_of_eat++;
	pthread_mutex_unlock(&philo->info->eat_mutex);
	ft_go_to_bed(philo->info->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	ft_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(philo->l_fork);
	ft_printer(philo, "has taken a fork");
	ft_printer(philo, "has taken a fork");
}

void	ft_go_to_bed(long long time)
{
	long long	finish_time;

	finish_time = time + ft_runtime_to_ms();
	while (finish_time > ft_runtime_to_ms())
	{
		usleep(100);
	}
}

void	ft_one_philo(t_philo *philo)
{
	ft_printer(philo, "has taken a fork");
	ft_go_to_bed(philo->info->time_to_die);
	ft_dead_msg(philo, "is dead");
	pthread_mutex_lock(&philo->info->check_mutex);
	philo->info->is_dead = 1;
	pthread_mutex_unlock(&philo->info->check_mutex);
}

void	ft_sleep(t_philo *philo)
{
	ft_printer(philo, "is sleeping");
	ft_go_to_bed(philo->info->time_to_sleep);
}
