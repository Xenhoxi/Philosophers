/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:25:47 by ljerinec          #+#    #+#             */
/*   Updated: 2023/06/28 14:15:50 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_msleep(int time)
{
	long	start;

	start = get_time_ms();
	while (get_time_ms() < (start + time))
		usleep(100);
}

long	get_time_ms(void)
{
	struct timeval	st_time;

	gettimeofday(&st_time, 0);
	return (st_time.tv_sec * 1000 + st_time.tv_usec / 1000);
}

void	philo_msg(t_philo *philo, char *msg)
{
	long int	time;

	pthread_mutex_lock(philo->lock_msg);
	pthread_mutex_lock(philo->check_state);
	time = get_exec_time(*philo->s_time);
	if (philo->state != 'D')
	{
		pthread_mutex_unlock(philo->check_state);
		printf("%ld Philo %d %s\n", time, philo->index + 1, msg);
	}
	else
		pthread_mutex_unlock(philo->check_state);
	pthread_mutex_unlock(philo->lock_msg);
}

void	change_state(t_phinfo *phinfo, char new_state)
{
	int	u;

	u = -1;
	while (phinfo->philo[++u])
	{
		pthread_mutex_lock(phinfo->philo[u]->check_state);
		phinfo->philo[u]->state = new_state;
		pthread_mutex_unlock(phinfo->philo[u]->check_state);
	}
}
