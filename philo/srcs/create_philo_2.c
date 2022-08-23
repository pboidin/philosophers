#include "../includes/philosophers.h"

pthread_mutex_t	*ft_init_l_fork(int i, int nb_ph, pthread_mutex_t *mut)
{
	(void)nb_ph;
	if (i == 0)
		return (&mut[i]);
	else
		return (&mut[i - 1]);
}

pthread_mutex_t *ft_init_r_fork(int i, int nb_ph, pthread_mutex_t *mut)
{
    if (i == 0)
		return (&mut[nb_ph - 1]);
	else
		return (&mut[i]);
}