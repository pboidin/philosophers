#include "../includes/philosophers.h"

void	ft_dead_msg(t_philo *philo, char *src)
{
	int	t;

	pthread_mutex_lock(&philo->info->print_mutex);
	t = ft_runtime_to_ms() - philo->info->start_time;
	printf("%dms %d %s\n", t, philo->id, src);
	pthread_mutex_unlock(&philo->info->print_mutex);
	return ;
}

void	ft_printer(t_philo *philo, char *src)
{
	int	t;

	pthread_mutex_lock(&philo->info->check_mutex);
	t = ft_runtime_to_ms() - philo->info->start_time;
	if (!philo->info->is_dead)
		printf("%dms %d %s\n", t, philo->id, src);
	pthread_mutex_unlock(&philo->info->check_mutex);
	return ;
}
