#include "../includes/philosophers.h"

int	ft_check_argv(char **argv)
{
	int	i;
	int	j;
	int	len;

	j = 0;
	i = 0;
	while (argv[++i])
	{
		len = ft_strlen(argv[i]);
		j = -1;
		while (++j < len)
		{
			if (ft_digit(argv[i][j]))
				continue ;
			return (ft_error("Wrong argument\n"));
		}
	}
	return (0);
}

int	ft_check_args(int argc, char **argv, t_info *master)
{
	if (argc != 5 && argc != 6)
		return (ft_error("Wrong argument\n"));
	ft_check_argv(argv);
	master->nb_ph = ft_atoi(argv[1]);
	master->time_to_die = ft_atoi(argv[2]);
	master->time_to_eat = ft_atoi(argv[3]);
	master->time_to_sleep = ft_atoi(argv[4]);
	if (master->nb_ph < 1 || master->time_to_die < 1
		|| master->time_to_eat < 1 || master->time_to_sleep < 1)
		return (ft_error("Wrong argument\n"));
	if (argc == 6)
	{
		master->must_eat = ft_atoi(argv[5]);
		if (master->must_eat < 1)
			return (ft_error("Wrong argument\n"));
	}
	else
		master->must_eat = 0;
	return (0);
}
