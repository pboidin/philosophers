#include "../includes/philosophers.h"

int	main (int argc, char **argv)
{
	t_info	master;

	if (ft_check_args(argc, argv, &master))
		return (1);
	if (ft_create_philo(&master))
	{
		ft_free_ph(&master);
		return (1);
	}
	master.start_time = ft_runtime_to_ms();
	if (ft_thread(&master))
	{
		ft_free_ph(&master);
		return (1);
	}
	ft_free_ph(&master);
	return(0);
}
