#include "philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	nb;
	int	tmp;

	i = 0;
	nb = 0;
	tmp = 0;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (str[i] - '0') + (nb * 10);
		i++;
		if (nb < tmp)
			return (0);
		tmp = nb;
	}
	if (str[i] != 0)
		return (0);
	return (nb);
}

void	ft_free_clear(t_philo *master)
{
	t_philo	*next;

	next = master;
	free(master);
	master = master->next;
	while (next != master && master != NULL)
	{
		free(master);
		master = master->next;
	}
}

void	ft_put_cmd(int n, int cmd)
{
	static pthread_mutex_t	pt;
	static pthread_mutex_t	*ptn = NULL;

	if (ptn == NULL)
	{
		ptn = &pt;
		pthread_mutex_init(ptn, NULL);
	}
	pthread_mutex_lock(ptn);
	if (cmd == FORK)
		printf("%llu %d has taken a fork\n", ft_runtime_to_ms(), n);
	else if (cmd == EAT)
		printf("%llu %d is eating\n", ft_runtime_to_ms(), n);
	else if (cmd == SLEEP)
		printf("%llu %d is sleeping\n", ft_runtime_to_ms(), n);
	else if (cmd == THINK)
		printf("%llu %d is thinking\n", ft_runtime_to_ms(), n);
	else
	{
		printf("%llu %d died\n", ft_runtime_to_ms(), n);
		return ;
	}
	pthread_mutex_unlock(ptn);
}

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

unsigned long long int	ft_runtime_to_ms(void)
{
	unsigned long long int			ms;
	static unsigned long long int	start = 0;
	static struct timeval			time;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000;
	ms += time.tv_usec / 1000;
	if (!start)
		start = ms;
	return (ms - start);
}