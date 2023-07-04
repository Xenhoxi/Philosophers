/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:07:48 by ljerinec          #+#    #+#             */
/*   Updated: 2023/07/04 11:01:27 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

# define TEXT_FORK "\033[33m has taken a fork !\033[0m"
# define TEXT_EAT "\033[32m is eating !\033[0m"
# define TEXT_SLEEP "\033[34m is sleeping !\033[0m"
# define TEXT_THINK "\033[35m is thinking !\033[0m"
# define TEXT_DEAD "\033[31m is dead !\033[0m"

typedef struct s_info
{
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	nb_meal;
}				t_info;

typedef struct s_philo
{
	int				index;
	pthread_t		thread;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*lock_msg;
	pthread_mutex_t	*check_state;
	pthread_mutex_t	*mutex_meal;
	char			state;
	t_info			*time_info;
	long int		*s_time;
	long int		last_meal;
	int				nb_meal;
	int				nb_philo;
}				t_philo;

typedef struct s_phinfo
{
	pthread_mutex_t	*lock_msg;
	pthread_t		checker;
	long int		start_time;
	t_philo			**philo;
	t_info			*time_info;
	int				nb_philo;
	int				philo_number;
}				t_phinfo;

// philo.c
void		run(t_phinfo *phinfo);
long		get_exec_time(long int time);

// threads.c
void		philo_eat(t_philo *philo);
void		*philo_life(void *param);
void		*big_brother(void *param);
int			is_philo_dead(t_phinfo *phinfo);
int			is_philo_eat_all(t_phinfo *phinfo);

// utils.c
void		change_state(t_phinfo *phinfo, char new_state);
void		philo_msg(t_philo *philo, char *msg);
long		get_time_ms(void);
void		ft_msleep(int time);

// parsing.c
t_phinfo	*setup(int argc, char **argv);
int			ft_atoi(char *str);
void		setup_each_philo(t_phinfo *phinfo);
t_philo		*create_philo(int i, t_phinfo *phinfo);
long		get_exec_time(long int time);

// checking.c
void		checking_argv(int argc, char **argv);
long long	ft_atoll(const char *str);
int			is_number(char *str);
int			ft_strlen(char *str);

// action.c
void		free_mutex_philo(t_phinfo *phinfo);
void		take_fork(t_philo *philo);
void		add_meal(t_philo *philo);
void		eat(t_philo *philo);
void		sleep_and_think(t_philo *philo);
void		wait_if_first_meal(t_philo *philo);
void		go_eat(t_philo *philo);
void		*only_one(t_philo *philo);

#endif