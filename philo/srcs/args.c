#include "../includes/philosophers.h"

int	ft_init_const(int argc, char **argv, const_t *ph_const)
{
	ph_const->nb_ph = ft_atoi(argv[0]);
	ph_const->time_to_die = ft_atoi(argv[1]);
	ph_const->time_to_eat = ft_atoi(argv[2]);
	ph_const->time_to_sleep = ft_atoi(argv[3]);
	if (ph_const->nb_ph < 1 || ph_const->time_to_die < 1
		|| ph_const->time_to_eat < 1 || ph_const->time_to_sleep < 1)
		return (6);
	if (argc == 4)
		ph_const->nb_rep = -1;
	else 
	{
		ph_const->nb_rep = ft_atoi(argv[argc - 1]);
		if (ph_const->nb_rep == -1)
			return (6);
	}
}

int	ft_checker_ph(char *argv)
{
	int	rslt;
	int	i;

	i = 0;
	rslt = 0;
	while(argv[i])
	{
		rslt = (rslt * 10) + (argv[i] - 48);
		i++;
		if (rslt > 200)
			return (4);
	}
	if (rslt == 0)
		return (5);
	return (0);
}

int	ft_checker_number(int argc, char *argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < argc)
	{
		while (argv[j])
		{
			if (argv[j] < '0' || argv[j] > '9')
				return (3);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_checker_argts(int argc, char **argv)
{
	int	key;

	if (argc < 5)
		return (1);
	else if (argc > 6)
		return (2);
	return (0);
}

int	ft_check_args(int argc, char **argv, const_t *ph_const)
{
	int key;

	if (key = ft_checker_argts(argc, argv) != 0)
		return (key);
	if (key = ft_checker_number(argc, argv) != 0)
		return (key);
	if (key = ft_checker_ph(argv) != 0)
		return (key);
	if (key = ft_init_const(argc, &argv[1], ph_const))
		return (key);
	return (0);
}
