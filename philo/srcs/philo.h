#ifndef	PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdint.h>
# include <sys/time.h>

# define PHILO_MAX 1000

typedef struct	s_philo {
	int				id;
	int				eat;
	int				left;
	int				right;
	long long 		time_eat;
	pthread_t		thread_p;
	struct s_info	*master;
}		t_philo;


typedef	struct	s_info {
	int				nb_ph;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	int				dead;
	int				all_eat;
	long long		birth_time;
	t_philo			philo[PHILO_MAX];
	pthread_mutex_t for_m[PHILO_MAX];
	pthread_mutex_t	act_m;
	pthread_mutex_t	eat_m;
}		t_info;

int						ft_atoi(char *str);
int						creation_process(t_info *master, char **argv);

long long int			ft_runtime_to_ms(void);

void					ft_eat(t_philo *philo);
void					ft_health_center(t_info *master, t_philo *philo);
void					ft_printer(t_info *master, char *str, int i);
void					ft_sleep(long long time, t_info *master);

#endif
