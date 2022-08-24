#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdint.h>
# include <string.h>

# define START 30

typedef struct	const_s
{
	int				nb_ph;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_rep;
}					const_t;

typedef struct	end_s
{
	pthread_mutex_t	mutex;
	int				end;
}					end_t;

typedef struct	philo_s
{
	int				id;
	long long		last_eat;
	pthread_mutex_t	mut_last_eat;
	int				num_of_eat;
	int				quota;
	long			begin_val;
	pthread_mutex_t	*log;
	int				left_fork;
	int				right_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	const_t			*ph_const;
	end_t			*end;
	end_t			*end_threads;
	pthread_mutex_t	*setup;
}					philo_t;

typedef struct	info_s
{
	long			begin;
	pthread_mutex_t	log;
	pthread_mutex_t	setup;
	pthread_mutex_t	*all_fork;
	pthread_t		*all_threads;
	philo_t			*philos;
	const_t			ph_const;
	end_t			end;
	end_t			end_threads;
}					info_t;

// Actions
void				ft_take_left_fork(philo_t *ph);
void				ft_take_right_fork(philo_t *ph);
int					ft_rout_loop(philo_t *ph);
void				ft_wait(philo_t *ph);
void				*ft_one_philo(void *args);

void				ft_sleep(philo_t *ph);
void				ft_eat(philo_t *ph);
long				ft_last_ph(philo_t *ph);
void				*ft_end(philo_t *ph);
void				*ft_routine(void *args);


// Args
int					ft_init_const(int argc, char **argv, const_t *ph_const);
int					ft_check_args(int argc, char **argv, const_t *ph_const);


// Create_Thread
int					ft_waiting_threads(info_t *info);
int					ft_init_threads(pthread_t *all_th, philo_t *all_ph, int nb_ph);

// Create_Philo
void				ft_free_forks(info_t *info);
void				ft_init_ph(info_t *info, philo_t *philo, long begin_v, int i);
int					ft_create_philos(info_t *info, int nb_ph);
int					ft_init_info(info_t *info, int nb_ph);

pthread_mutex_t		*ft_init_l_fork(int i, int nb_ph, pthread_mutex_t *mut);
pthread_mutex_t 	*ft_init_r_fork(int i, int nb_ph, pthread_mutex_t *mut);

// Printer
int					ft_printer_thread_error(info_t *info, int key);
void				ft_printer(philo_t *ph, int id, long begin_val, char *str);
void				ft_printer_error(int key);

// Tools
long				timestamp(long begin);
void				msleep(long time, long start);
int					ft_atoi(char *str);
void				ft_free_table(info_t *info);

#endif 
