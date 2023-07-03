/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:10:32 by ljerinec          #+#    #+#             */
/*   Updated: 2023/07/03 13:30:07 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	sleep_and_think(t_philo *philo)
{
	philo_msg(philo, TEXT_SLEEP);
	pthread_mutex_lock(philo->check_state);
	if (philo->state != 'D')
	{
		pthread_mutex_unlock(philo->check_state);
		ft_msleep(philo->time_info->t_sleep);
	}
	else
		pthread_mutex_unlock(philo->check_state);
	philo_msg(philo, TEXT_THINK);
}

void	add_meal(t_philo *philo)
{
	pthread_mutex_lock(philo->check_state);
	if (philo->state != 'D')
	{
		pthread_mutex_unlock(philo->check_state);
		pthread_mutex_lock(philo->mutex_meal);
		philo->nb_meal++;
		pthread_mutex_unlock(philo->mutex_meal);
	}
	else
		pthread_mutex_unlock(philo->check_state);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->check_state);
	if (philo->state != 'D')
	{
		pthread_mutex_unlock(philo->check_state);
		pthread_mutex_lock(philo->mutex_meal);
		philo->last_meal = get_exec_time(*philo->s_time);
		pthread_mutex_unlock(philo->mutex_meal);
		pthread_mutex_lock(philo->check_state);
		philo->state = 'E';
		pthread_mutex_unlock(philo->check_state);
		ft_msleep(philo->time_info->t_eat);
	}
	else
		pthread_mutex_unlock(philo->check_state);
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->check_state);
	if (philo->index % 2 == 0)
	{
		if (philo->nb_philo > 1)
		{
			pthread_mutex_lock(philo->fork_right);
			philo_msg(philo, TEXT_FORK);
		}
		pthread_mutex_lock(philo->fork_left);
		philo_msg(philo, TEXT_FORK);
	}
	else
	{
		if (philo->nb_meal == 0)
			ft_msleep(5);
		pthread_mutex_lock(philo->fork_left);
		philo_msg(philo, TEXT_FORK);
		if (philo->nb_philo > 1)
		{
			pthread_mutex_lock(philo->fork_right);
			philo_msg(philo, TEXT_FORK);
		}
	}
}

void	go_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->check_state);
	if (philo->state != 'D')
	{
		pthread_mutex_unlock(philo->check_state);
		philo_eat(philo);
	}
	else
		pthread_mutex_unlock(philo->check_state);
}
