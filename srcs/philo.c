#include "philo.h"

int	main(int argc, char **argv)
{
	int			nb_ph;
	t_philo		*master;
	pthread_t	health;

	if (ft_check_args(argc, argv))
		return (1);
	master = ft_philo_creator(argc, argv);
	if (!master)
		return (1);
	nb_ph = ft_atoi(argv[1]);
	while (nb_ph--)
	{
		pthread_mutex_init(&master->fork, NULL);
		pthread_create(&master->thread_data, NULL, &ft_philo_life, master);
		master = master->next;
	}
	pthread_create(&health, NULL, &ft_health_check, master);
	pthread_join(health, NULL);
	nb_ph = ft_atoi(argv[1]);
	while (nb_ph--)
	{
		pthread_detach(master->thread_data);
		master = master->next;
	}
}
