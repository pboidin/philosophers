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

static void	ft_free_philo(philo_t *ph)
{
	int	i;

	i = -1;
	while (++i < ph->ph_const->nb_ph)
		pthread_mutex_destroy(&(ph[i].mut_last_eat));
	free(ph);
}

void	ft_free_table(info_t *info)
{
	free_forks(info);
	pthread_mutex_destroy(&info->end.mutex);
	pthread_mutex_destroy(&info->end_threads.mutex);
	pthread_mutex_destroy(&info->setup);
	pthread_mutex_destroy(&info->log);
	free_philo(info->philos);
	free(info->all_threads);
}
