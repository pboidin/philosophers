#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdint.h>

# define MAX_PHILO 200

typedef struct s_philo {
	int					id;
	int					eat;
	int					left;
	int					right;
	long long			eat_time;
	pthread_t			thread_p;
	struct s_info		*master;
}	t_philo;

typedef struct s_info {
	int					nb_ph;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_eat;
	int					dead;
	int					all_eat;
	long long			birth_time;
	pthread_mutex_t		eat_m;
	pthread_mutex_t		act_m;
	pthread_mutex_t		for_m[MAX_PHILO];
	t_philo				philo[MAX_PHILO];
}	t_info;

int				ft_atoi(char *str);
int				ft_creation_process(t_info *master, char **av);
int				ft_init_mutex(t_info *master);
int				ft_init_philo(t_info *master);
int				ft_life_creator(t_info *master);
long long		ft_runtime_to_ms(void);
void			ft_eat(t_philo *philo);
void			ft_health_check(t_info *master, t_philo *philo);
void			ft_nbr_one(t_philo *philo);
void			ft_printer(t_info *master, int id, char *str);
void			ft_remove(t_info *master, t_philo *philo);
void			ft_sleep(long long time, t_info *master);
void			*ft_philo_life(void *void_philo);

#endif
