/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:16:35 by ljerinec          #+#    #+#             */
/*   Updated: 2023/07/03 13:22:02 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	checking_argv(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		printf("Error ! Not enough parameters !\n");
		printf("You should try like this :\n");
		printf("./philo 4 410 200 200 5\n");
		printf("	----	\n");
		printf("./philo 5 810 200 200\n");
		exit(1);
	}
	while (i < argc)
	{
		if (is_number(argv[i]) == 1)
			i++;
		else
		{
			printf("Only numbers allowed for the parameters !\n");
			exit(1);
		}
	}
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

long long	ft_atoll(const char *str)
{
	int			i;
	long long	negatif;
	long long	resultat;

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
