#include "../includes/philosophers.h"

void	ft_free_forks(info_t *info)
{
	int	i;

	i = 0;
	while (i++ < info->ph_const.nb_ph)
		pthread_mutex_destroy(&info->all_fork[i]);
	free(info->all_fork);
}

void	ft_init_ph(info_t *info, philo_t *philo, long begin_v, int i)
{
	philo->id = i + 1;
	philo->last_eat = 0;
	pthread_mutex_init(&(philo->mut_last_eat), 0);
	philo->num_of_eat = 0;
	philo->quota = 0;
	philo->begin_val = begin_v;
	philo->log = &info->log;
	philo->left_fork = 0;
	philo->right_fork = 0;
	philo->l_fork = ft_init_l_fork(i, info->ph_const.nb_ph, info->all_fork);
	philo->r_fork = ft_init_r_fork(i, info->ph_const.nb_ph, info->all_fork);
	philo->ph_const = &info->ph_const;
	philo->end = &(info->end);
	philo->end_threads = &(info->end_threads);
	philo->setup = &(info->setup);
}

int	ft_create_philos(info_t *info, int nb_ph)
{
	int				i;
	struct timeval	begin;
	long			begin_val;

	i = 0;
	info->philos = malloc(sizeof(philo_t) * (nb_ph + 1));
	if (!info->philos)
		return (7);
	memset(info->philos, 0, sizeof(philo_t) * (nb_ph + 1));
	gettimeofday(&begin, 0);
	begin_val = begin.tv_sec * 1000 + begin.tv_usec / 1000;
	info->begin = begin_val;
	while (i < nb_ph)
	{
		ft_init_ph(info, &info->philos[i], begin_val, i);
		i++;
	}
	return (0);
}

static int	ft_init_forks(info_t *info, int nb_ph)
{
	int	i;

	i = 0;
	info->all_fork = malloc(sizeof(pthread_mutex_t) * (nb_ph + 1));
	if (!info->all_fork)
		return (7);
	memset(info->all_fork, 0, sizeof(pthread_mutex_t) * (nb_ph + 1));
	while (i++ < nb_ph)
		pthread_mutex_init(&info->all_fork[i], 0);
	return (0);
}

int	ft_init_info(info_t *info, int nb_ph)
{
	int	key;

	key = ft_init_forks(info, nb_ph);
	if (key)
		return (key);
	key = ft_create_philos(info, nb_ph);
	if (key)
		return (ft_free_forks(info), key);
	info->all_threads = malloc(sizeof(pthread_t) * (nb_ph + 1));
	if (!info->all_threads)
		return (ft_free_forks(info), free(info->philos), 7);
	memset(info->all_threads, 0, sizeof(pthread_t) * (nb_ph + 1));
	pthread_mutex_init(&info->log, 0);
	pthread_mutex_init(&info->end.mutex, 0);
	info->end.end = 0;
	pthread_mutex_init(&info->end_threads.mutex, 0);
	info->end_threads.end = 0;
	pthread_mutex_init(&info->setup, 0);
	return (0);
}
