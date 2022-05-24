#include "philo.h"

int		add_new_philo(t_philo *master, int n, int argc, char **argv)
{
	t_philo	*new;

	new = (t_philo *)malloc(sizeof(t_philo));
	if (!new)
		return (ft_free_clear(master), 0);
	while (master->next)
		master = master->next;
	new->n = n;
	new->die = ft_atoi(argv[2]);
	new->eat = ft_atoi(argv[3]);
	new->sleep = ft_atoi(argv[4]);
	new->nb_philo_must_eat = -1;
	new->last_eat = 0;
	if (argc == 6)
		new->nb_philo_must_eat = ft_atoi(argv[5]);
	new->next = NULL;
	master->next = new;
	return (1);
}

t_philo	*ft_philo_creator(int argc, char **argv)
{
	int		i;
	t_philo	*ph;
	t_philo *last;

	i = 2;
	ph = (t_philo *)malloc(sizeof(t_philo));
	if (ph == NULL)
		return (NULL);
	ph->n = 1;
	ph->die = ft_atoi(argv[2]);
	ph->eat = ft_atoi(argv[3]);
	ph->sleep = ft_atoi(argv[4]);
	ph->nb_philo_must_eat = -1;
	ph->last_eat = 0;
	if (argc == 6)
		ph->nb_philo_must_eat = ft_atoi(argv[5]);
	ph->next = NULL;
	while (i <= ft_atoi(argv[1]))
		if (add_new_philo(ph, i++, argc, argv) == 0)
			return (NULL);
	last = ph;
	while (last->next)
		last = last->next;
	last->next = ph;
	return (ph);
}

void	*ft_philo_life(void *voidarg)
{
	t_philo	*ph;

	ph = (t_philo *)voidarg;
	while (1)
	{
		if (ft_runtime_to_ms() == 0 && ph->n % 2 == 0)
			usleep(ph->eat * 1000);
		pthread_mutex_lock(&ph->fork);
		ft_put_cmd(ph->n, FORK);
		pthread_mutex_lock(&ph->next->fork);
		ph->current = EAT;
		ft_put_cmd(ph->n, FORK);
		ph->last_eat = ft_runtime_to_ms();
		ft_put_cmd(ph->n, EAT);
		usleep(ph->eat * 1000);
		if (ph->nb_philo_must_eat > 0)
			ph->nb_philo_must_eat--;
		ft_put_cmd(ph->n, SLEEP);
		pthread_mutex_unlock(&ph->fork);
		pthread_mutex_unlock(&ph->next-> fork);
		usleep(ph->sleep * 1000);
		ft_put_cmd(ph->n, THINK);
		ph->current = THINK;
	}
	return (NULL);
}

int		ft_all_eat(t_philo *ph)
{
	t_philo	*turn;

	turn = ph->next;
	while (turn != ph)
	{
		if (turn->nb_philo_must_eat > 0)
			return (0);
		turn = turn->next;
	}
	return (1);
}

void	*ft_health_check(void *voidarg)
{
	t_philo	*ph;

	ph = (t_philo *)voidarg;
	while (1)
	{
		if (ph->nb_philo_must_eat == 0 && ft_all_eat(ph))
			return (NULL);
		if (ph->last_eat + ph->die + 5 < ft_runtime_to_ms())
		{
			ft_put_cmd(ph->n, DEAD);
			return (NULL);
		}
		ph = ph->next;
	}
}