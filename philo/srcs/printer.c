#include "../includes/philosophers.h"

int	ft_printer_thread_error(info_t *info, int key)
{
	pthread_mutex_lock(&(info->end.mutex));
	info->end.end = 1;
	pthread_mutex_unlock(&(info->end.mutex));
	ft_waiting_threads(info);
	return (ft_printer_error(key), ft_free_table(info), 1);
}

static int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (*(s1 + i) != 0 && *(s2 + i) != 0 && *(s1 + i) == *(s2 + i))
		i++;
	return ((unsigned char)*(s1 + i) - (unsigned char)*(s2 + i));
}

void	ft_printer(philo_t *ph, int id, long begin_val, char *str)
{
	pthread_mutex_lock(&(ph->mut_last_eat));
	pthread_mutex_lock(ph->log);
	pthread_mutex_lock(&(ph->end->mutex));
	if (!ft_strcmp(str, "is eating"))
		ph->last_eat = timestamp(ph->begin_val);
	if (!ph->end->end && !(timestamp(ph->begin_val) - ph->last_eat >= (long)ph->ph_const->time_to_die))
		printf("%li %d %s\n", timestamp(begin_val), id, str);
	pthread_mutex_unlock(&(ph->mut_last_eat));
	pthread_mutex_unlock(ph->log);
	pthread_mutex_unlock(&(ph->end->mutex));
}

static void	ft_printer_error_2(int key)
{
	if (key == 1)
		write(2, "Less than four arguments\n", 26);
	else if (key == 2)
		write(2, "Too much Arguments\n", 20);
	else if (key == 3)
		write(2, "Arguments must be positive numbers\n", 36);
	write(2, "Usage: ./philo <numbers_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n", 130);
}

void	ft_printer_error(int key)
{
	if (key < 4)
		ft_printer_error_2(key);
	else if (key == 4)
		write(2, "Too much philosopher maximum: 200\n", 34);
	else if (key == 5)
		write(2, "Minimum one philosophers \n", 26);
	else if (key == 6)
		write(2, "Wrong Arguments\n", 16);
	else if (key == 7)
		write(2, "Malloc error\n", 14);
	else if (key == 8)
		write(2, "Thread error\n", 14);
}
