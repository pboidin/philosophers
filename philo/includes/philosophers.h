/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piboidin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 22:56:57 by piboidin          #+#    #+#             */
/*   Updated: 2022/08/24 23:25:24 by piboidin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdint.h>
# include <string.h>

# define START 30

typedef struct s_const
{
	int				nb_ph;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_rep;
}					t_const;

typedef struct s_end
{
	pthread_mutex_t	mutex;
	int				end;
}					t_end;

typedef struct s_philo
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
	t_const			*ph_const;
	t_end			*end;
	t_end			*t_endhreads;
	pthread_mutex_t	*setup;
}					t_philo;

typedef struct s_info
{
	long			begin;
	pthread_mutex_t	log;
	pthread_mutex_t	setup;
	pthread_mutex_t	*all_fork;
	pthread_t		*all_threads;
	t_philo			*philos;
	t_const			ph_const;
	t_end			end;
	t_end			t_endhreads;
}					t_info;

void		ft_take_left_fork(t_philo *ph);
void		ft_take_right_fork(t_philo *ph);
int			ft_rout_loop(t_philo *ph);
void		ft_wait(t_philo *ph);
void		*ft_one_philo(void *args);
void		ft_sleep(t_philo *ph);
void		ft_eat(t_philo *ph);
long		ft_last_ph(t_philo *ph);
void		*ft_end(t_philo *ph);
void		*ft_routine(void *args);
int			ft_init_const(int argc, char **argv, t_const *ph_const);
int			ft_check_args(int argc, char **argv, t_const *ph_const);
int			ft_waiting_threads(t_info *info);
int			ft_init_threads(pthread_t *all_th, t_philo *all_ph, int nb_ph);
void		ft_free_forks(t_info *info);
void		ft_init_ph(t_info *info, t_philo *philo, long begin_v, int i);
int			ft_create_philos(t_info *info, int nb_ph);
int			ft_init_info(t_info *info, int nb_ph);
int			ft_printer_thread_error(t_info *info, int key);
void		ft_printer(t_philo *ph, int id, long begin_val, char *str);
void		ft_printer_error(int key);
long		timestamp(long begin);
void		msleep(long time, long start);
int			ft_atoi(char *str);
void		ft_free_table(t_info *info);

#endif 
