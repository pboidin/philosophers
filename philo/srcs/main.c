#include "philo.h"

int	ft_check_args(int argc, char **argv)
{
	int		i;

	i = 1;
	if (argc < 5)
		return (write(STDERR_FILENO, "Error:\nArguments needed\n", 24));
	if (argc > 6)
		return (write(STDERR_FILENO, "Error:\nToo many arguments\n", 26));
	while (i < argc)
		if (ft_atoi(argv[i++]) <= 0)
			return (write(STDERR_FILENO, "Error:\nA non-valid argument\n", 28));
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	master;

	if (ft_check_args(argc, argv))
		return (1);
	if (!(creation_process(&master, argv)))
		return (write(STDERR_FILENO, "Error:\nParsing Wrong\n", 21), 1);
//	if (!(life_creator(&master)))
//		return (write(STDERR_FILENO, "Error:\nThreads Creation\n", 24), 1);
	return (0);
}
