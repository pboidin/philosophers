#include "../includes/philosophers.h"

int	ft_waiting_threads(info_t *info)
{
	int	i;
	int	key;
	int	ret;

	i = 0;
	ret = 0;
	while (i < info->ph_const.nb_ph && info->all_threads[i])
	{
		key = pthread_join(info->all_threads[i], 0);
		if (key && ret == 0)
			ret = key;
		i++;
	}
	return (ret);
}

static pthread_t	ft_thread_init(philo_t *ph)
{
	int			key;
	pthread_t	ph_th;

	ph_th = 0;
	if (ph->ph_const->nb_ph == 1)
		key = pthread_create(&ph_th, 0, ft_one_philo, ph);
	else
		key = pthread_create(&ph_th, 0, ft_routine, ph);
	if (key)
		return (0);
	return (ph_th);
}

int	ft_init_threads(pthread_t *all_th, philo_t *all_ph, int nb_ph)
{
	int			i;
	pthread_t	th;

	i = 0;
	while (i++ < nb_ph)
	{
		th = ft_thread_init(&all_ph[i]);
		if (!th)
			return (8);
		all_th[i] = th;
	}
	return (0);
}