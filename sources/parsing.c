/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:42:14 by ljerinec          #+#    #+#             */
/*   Updated: 2023/07/03 12:33:09 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_phinfo	*setup(int argc, char **argv)
{
	t_phinfo	*phinfo;

	phinfo = malloc(sizeof(t_phinfo));
	phinfo->philo = NULL;
	phinfo->nb_philo = ft_atoi(argv[1]);
	phinfo->time_info = malloc(sizeof(t_info));
	phinfo->time_info->t_die = ft_atoi(argv[2]);
	phinfo->time_info->t_eat = ft_atoi(argv[3]);
	phinfo->time_info->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		phinfo->time_info->nb_meal = ft_atoi(argv[5]);
	else
		phinfo->time_info->nb_meal = -1;
	return (phinfo);
}

void	setup_each_philo(t_phinfo *phinfo)
{
	int				i;

	i = 0;
	phinfo->lock_msg = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(phinfo->lock_msg, NULL);
	phinfo->philo = malloc(sizeof(t_philo *) * (phinfo->nb_philo + 1));
	while (i < phinfo->nb_philo)
	{
		phinfo->philo[i] = create_philo(i, phinfo);
		i++;
	}
	phinfo->philo[i] = NULL;
	i = 0;
	while (phinfo->philo[i])
	{
		if (phinfo->philo[i + 1])
			phinfo->philo[i]->fork_right = phinfo->philo[i + 1]->fork_left;
		else if (phinfo->nb_philo > 1)
			phinfo->philo[i]->fork_right = phinfo->philo[0]->fork_left;
		phinfo->philo[i]->lock_msg = phinfo->lock_msg;
		i++;
	}
}

t_philo	*create_philo(int i, t_phinfo *phinfo)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	philo->fork_left = malloc(sizeof(pthread_mutex_t));
	philo->check_state = malloc(sizeof(pthread_mutex_t));
	philo->mutex_meal = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo->fork_left, NULL);
	pthread_mutex_init(philo->check_state, NULL);
	pthread_mutex_init(philo->mutex_meal, NULL);
	philo->thread = NULL;
	philo->s_time = &phinfo->start_time;
	philo->time_info = phinfo->time_info;
	philo->state = 'W';
	philo->nb_meal = 0;
	philo->nb_philo = phinfo->nb_philo;
	philo->last_meal = 0;
	philo->index = i;
	return (philo);
}

int	ft_atoi(char *str)
{
	int	i;
	int	negatif;
	int	resultat;

	resultat = 0;
	negatif = 1;
	i = 0;
	while (str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			negatif = -negatif;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		resultat = resultat * 10 + str[i] - '0';
		i++;
	}
	return (resultat * negatif);
}
