#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdint.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				num_of_eat;
	int				time_to_die;
	long long		last_eat;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	struct s_info	*info;
}					t_philo;

typedef struct	s_info
{
	int				nb_ph;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	long long		start_time;
	int				is_dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	die_mutex;
	pthread_mutex_t	check_mutex;
	pthread_mutex_t	last_eat_mutex;
	pthread_mutex_t	eat_mutex;
	t_philo			*philos;
}					t_info;

// Actions
void		ft_eat(t_philo *philo);
void		ft_forks(t_philo *philo);
void		ft_go_to_bed(long long time);
void		ft_one_philo(t_philo *philo);
void		ft_sleep(t_philo *philo);

// Actions_2
int			ft_check_death(t_philo *philo);
void		ft_think(t_philo *philo);

// Args
int			ft_check_args(int argc, char **argv, t_info *master);
int			ft_check_argv(char **argv); 

// Create_Philo
int			ft_create_master(t_info *master);
int			ft_create_philo(t_info *master);
int			ft_malloc_philo(t_info *master);
int			ft_thread(t_info *master);
void		ft_free_ph(t_info *master);

// Printer
void		ft_dead_msg(t_philo *philo, char *src);
void		ft_printer(t_philo *philo, char *src);

// Routine
int			ft_check_must_eat(t_info *master);
int			ft_dead_checker(t_philo *philo);
void		*ft_check_eat(void *p);
void		*ft_check_routine(void *info);
void		*ft_routine(void *info);

// Tools
int			ft_atoi(char *str);
int			ft_error(char *message);
int			ft_digit(char c);
int			ft_strlen(char *str);
long long	ft_runtime_to_ms(void);

#endif 
