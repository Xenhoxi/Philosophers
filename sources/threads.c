/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:16:56 by ljerinec          #+#    #+#             */
/*   Updated: 2023/07/04 11:02:30 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->check_state);
	if (philo->state != 'D')
		take_fork(philo);
	else
		pthread_mutex_unlock(philo->check_state);
	if (philo->nb_philo > 1)
	{
		philo_msg(philo, TEXT_EAT);
		eat(philo);
		add_meal(philo);
		pthread_mutex_lock(philo->mutex_meal);
		if (philo->nb_meal == philo->time_info->nb_meal)
		{
			pthread_mutex_unlock(philo->mutex_meal);
			pthread_mutex_lock(philo->check_state);
			philo->state = 'F';
			pthread_mutex_unlock(philo->check_state);
		}
		else
			pthread_mutex_unlock(philo->mutex_meal);
	}
	pthread_mutex_unlock(philo->fork_left);
	if (philo->nb_philo > 1)
		pthread_mutex_unlock(philo->fork_right);
}

void	*philo_life(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (1)
	{
		if (philo->nb_philo == 1)
			return (only_one(philo));
		go_eat(philo);
		if (philo->nb_philo > 1)
		{
			sleep_and_think(philo);
			pthread_mutex_lock(philo->check_state);
			if (philo->state == 'D' || philo->state == 'F')
			{
				pthread_mutex_unlock(philo->check_state);
				break ;
			}
			else
				pthread_mutex_unlock(philo->check_state);
		}
	}
	return (NULL);
}

void	*big_brother(void *param)
{
	t_phinfo	*phinfo;

	phinfo = (t_phinfo *)param;
	while (1)
	{
		if (is_philo_eat_all(phinfo) == 1)
			break ;
		else if (is_philo_dead(phinfo) == 1)
		{
			change_state(phinfo, 'D');
			break ;
		}
	}
	return (NULL);
}

int	is_philo_dead(t_phinfo *phinfo)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (phinfo->philo[++i])
	{
		philo = phinfo->philo[i];
		pthread_mutex_lock(phinfo->philo[i]->mutex_meal);
		pthread_mutex_lock(phinfo->philo[i]->check_state);
		if (get_exec_time(*philo->s_time) - philo->last_meal
			> philo->time_info->t_die && philo->state != 'F')
		{
			pthread_mutex_unlock(phinfo->philo[i]->mutex_meal);
			pthread_mutex_unlock(phinfo->philo[i]->check_state);
			philo_msg(philo, TEXT_DEAD);
			change_state(phinfo, 'D');
			return (1);
		}
		else
		{
			pthread_mutex_unlock(phinfo->philo[i]->mutex_meal);
			pthread_mutex_unlock(phinfo->philo[i]->check_state);
		}
	}
	return (0);
}

int	is_philo_eat_all(t_phinfo *phinfo)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (phinfo->philo[++i])
	{
		pthread_mutex_lock(phinfo->philo[i]->check_state);
		if (phinfo->philo[i]->state == 'F')
			count++;
		pthread_mutex_unlock(phinfo->philo[i]->check_state);
	}
	if (count == phinfo->nb_philo)
		return (1);
	return (0);
}
