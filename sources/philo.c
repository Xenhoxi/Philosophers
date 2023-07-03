/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:06:28 by ljerinec          #+#    #+#             */
/*   Updated: 2023/07/03 12:35:32 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_phinfo		*phinfo;
	struct timeval	time;

	gettimeofday(&time, 0);
	checking_argv(argc, argv);
	phinfo = setup(argc, argv);
	setup_each_philo(phinfo);
	printf("Start of the simulation !\n");
	run(phinfo);
	return (0);
}

long	get_exec_time(long int time)
{
	struct timeval	st_time;

	gettimeofday(&st_time, 0);
	return ((st_time.tv_sec * 1000 + st_time.tv_usec / 1000) - time);
}

void	run(t_phinfo *phinfo)
{
	int				i;

	i = 0;
	phinfo->start_time = get_time_ms();
	pthread_create(&phinfo->checker, NULL,
		(void *) big_brother, (void *) phinfo);
	while (phinfo->philo[i])
	{
		pthread_create(&phinfo->philo[i]->thread, NULL,
			(void *) philo_life, (void *) phinfo->philo[i]);
		i++;
	}
	i = 0;
	while (phinfo->philo[i])
		pthread_join(phinfo->philo[i++]->thread, NULL);
	pthread_join(phinfo->checker, NULL);
	free_mutex_philo(phinfo);
}

void	free_mutex_philo(t_phinfo *phinfo)
{
	int	i;

	i = -1;
	while (phinfo->philo[++i])
	{
		pthread_mutex_destroy(phinfo->philo[i]->check_state);
		pthread_mutex_destroy(phinfo->philo[i]->mutex_meal);
		pthread_mutex_destroy(phinfo->philo[i]->fork_left);
		free(phinfo->philo[i]->check_state);
		free(phinfo->philo[i]->mutex_meal);
		free(phinfo->philo[i]->fork_left);
		free(phinfo->philo[i]);
	}
	pthread_mutex_destroy(phinfo->lock_msg);
	free(phinfo->lock_msg);
	free(phinfo->philo);
	free(phinfo);
}
