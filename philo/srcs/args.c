#include "../includes/philosophers.h"

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

static int	ft_checker_number2(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] > '9' || argv[i] < '0')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_checker_number(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!ft_checker_number2(argv[i]))
			return (3);
		i++;
	}
	return (0);
}

static int	ft_checker_argts(int argc)
{
	if (argc < 5)
		return (1);
	else if (argc > 6)
		return (2);
	return (0);
}

int	ft_check_args(int argc, char **argv, const_t *ph_const)
{
	int key;

	key = ft_checker_argts(argc);
	if (key)
		return (key);
	key = ft_checker_number(argc, argv);
	if (key)
		return (key);
	key = ft_checker_ph(argv[1]);
	if (key)
		return (key);
	key = ft_init_const(argc - 1, &argv[1], ph_const);
	if (key)
		return (key);
	return (0);
}
