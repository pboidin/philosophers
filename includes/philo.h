#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int						n;
	struct s_philo			*next;
	pthread_mutex_t			fork;
	pthread_t				thread_data;
	unsigned long long int	die;
	unsigned long long int	eat;
	unsigned long long int	sleep;
	unsigned long long int	last_eat;
	unsigned long long int	nb_meals;
	unsigned long long int	nb_philo_must_eat;
	unsigned long long int	current;
}				t_philo;

# define DEAD 0
# define THINK 1
# define EAT 2
# define SLEEP 3
# define FORK 4

int						add_new_philo(t_philo *master, int n, int argc, char **argv);
int						ft_all_eat(t_philo *ph);
int						ft_atoi(char *str);
int						ft_check_args(int argc, char **argv);

t_philo					*ft_philo_creator(int argc, char **argv);

unsigned long long int	ft_runtime_to_ms(void);

void					ft_free_clear(t_philo *master);
void					ft_put_cmd(int n, int cmd);

void					*ft_health_check(void *voidarg);
void					*ft_philo_life(void *voidarg);

#endif
