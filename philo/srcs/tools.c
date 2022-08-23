#include "../includes/philosophers.h"

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

void	msleep(long time, long start)
{
	while (timestamp(start) < (long)time)
		usleep(300);
}

long	timestamp(long begin)
{
	struct timeval	time;
	long			time_value;

	gettimeofday(&time, 0);
	time_value = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (time_value - begin);
}

static void	ft_free_philo(philo_t *ph)
{
	int	i;

	i = 0;
	while (i < ph->ph_const->nb_ph)
	{
		write(1, "FREEE\n", 6);
		pthread_mutex_destroy(&(ph[i].mut_last_eat));
		i++;
	}
	free(ph);
}

void	ft_free_table(info_t *info)
{
	ft_free_forks(info);
	pthread_mutex_destroy(&info->end.mutex);
	pthread_mutex_destroy(&info->end_threads.mutex);
	pthread_mutex_destroy(&info->setup);
	pthread_mutex_destroy(&info->log);
	ft_free_philo(info->philos);
	write(1, "PASSE\n", 6);
	free(info->all_threads);
}
