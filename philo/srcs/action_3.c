#include "../includes/philosophers.h"

static void	check_last_meal(info_t *info, int *stop, int i, int die)
{
	pthread_mutex_lock(&(info->philos[i].mut_last_eat));
	if (timestamp(info->begin) - info->philos[i].last_eat >= (long)die)
	{
		pthread_mutex_lock(&(info->end.mutex));
		info->end.end = 1;
		pthread_mutex_unlock(&(info->end.mutex));
		pthread_mutex_lock(&info->log);
		printf("%li %d %s\n", timestamp(info->begin),
			info->philos[i].id, "died");
		pthread_mutex_unlock(&info->log);
		*stop = 1;
	}
	pthread_mutex_unlock(&(info->philos[i].mut_last_eat));
}

static void	ft_dead_checker(info_t *info, int die, int nb_ph)
{
	int	i;
	int	stop;

	i = 0;
	pthread_mutex_lock(&(info->end.mutex));
	stop = info->end.end;
	pthread_mutex_unlock(&(info->end.mutex));
	if (stop)
		return ;
	while (i++ < nb_ph)
	{
		ft_last_eat(info, &stop, i, die);
		if (stop)
			break ;
	}
	msleep(1, timestamp(0));
}

static int	ft_check_end(info_t *info)
{
	pthread_mutex_lock(&(info->end.mutex));
	pthread_mutex_lock(&info->end_threads.mutex);
	if (info->end_threads.end == info->ph_const.nb_ph
        || info->end.end == 1 || info->ph_const.nb_rep == 0)
	{
		info->end.end = 1;
		return (pthread_mutex_unlock(&(info->end_threads.mutex)),
			pthread_mutex_unlock(&(info->end.mutex)), 0);
	}
	return (pthread_mutex_unlock(&(info->end_threads.mutex)),
		pthread_mutex_unlock(&(info->end.mutex)), 1);
}