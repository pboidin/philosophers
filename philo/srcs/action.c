#include "../includes/philosophers.h"

void	ft_take_left_fork(philo_t *ph)
{
	pthread_mutex_lock(ph->l_fork);
	ph->left_fork = 1;
	log_print(ph, ph->id, ph->begin_val, "has taken a fork");
}

void	ft_take_right_fork(philo_t *ph)
{
	pthread_mutex_lock(ph->r_fork);
	ph->right_fork = 1;
	log_print(ph, ph->id, ph->begin_val, "has taken a fork");
}

int		ft_rout_loop(philo_t *ph)
{
	pthread_mutex_lock(&(ph->end->mutex));
	if (ph->end->end == 1 || ph->ph_const->nb_rep == 0)
		return (pthread_mutex_unlock(&(ph->end->mutex)), 0);
	pthread_mutex_unlock(&(ph->end->mutex));
	pthread_mutex_lock(&(ph->mut_last_eat));
	if (timestamp(ph->begin_val) - ph->last_eat >= (long)ph->ph_const->time_to_die)
		return (pthread_mutex_unlock(&(ph->mut_last_eat)), 0);
	pthread_mutex_unlock(&(ph->mut_last_eat));
	if (ph->ph_const->nb_rep == -1)
		return (1);
	if (ph->num_of_eat >= ph->ph_const->nb_rep && ph->quota == 0)
	{
		pthread_mutex_lock(&(ph->end_threads->mutex));
		ph->end_threads->end += 1;
		pthread_mutex_unlock(&(ph->end_threads->mutex));
		ph->quota = 1;
	}
	return (1);
}

void	ft_wait(philo_t *ph)
{
	while (timestamp(ph->begin_val) < 30)
		usleep(300);
	ph->begin_val += 30;
}

void	*ft_one_philo(void *args)
{
	philo_t	*ph;

	ph = (philo_t *)args;
	ft_wait(ph);
	ft_printer(ph, ph->id, ph->begin_val, "is thinking");
	if (ft_rout_loop(ph))
		ft_take_left_fork(ph);
	while (ft_rout_loop(ph))
		usleep(200);
	return (ft_end(ph));
}
