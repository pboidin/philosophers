#include "../includes/philosophers.h"

int	ft_check_death(t_philo *philo)
{
	int	dead;

	dead = 0;
	pthread_mutex_lock(&philo->info->check_mutex);
	if (philo->info->is_dead)
		dead = 1;
	pthread_mutex_unlock(&philo->info->check_mutex);
	return (dead);
}

void	ft_think(t_philo *philo)
{
	ft_printer(philo, "is thinking");
}
