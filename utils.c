/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:55:14 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/10/19 15:39:05 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	is_full(t_philo *philo)
{
	if (philo->meals >= philo->data->nbr_meals
		&& philo->data->nbr_meals != 0 && !philo->full)
	{
		philo->full = true;
		philo->data->philos_full++;
	}
}

int	is_dead(t_philo *philo)
{
	bool	dead;

	dead = false;
	pthread_mutex_lock(&philo->lock);
	pthread_mutex_lock(&philo->data->finished_lock);
	if (get_time() >= philo->time_to_die || philo->data->finished)
	{
		if (!philo->data->finished)
			logs(philo, DEAD);
		philo->data->finished = true;
	}
	pthread_mutex_lock(&philo->data->lock);
	is_full(philo);
	if (philo->data->philos_full == philo->data->nbr_philo)
		philo->data->finished = true;
	dead = philo->data->finished;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(&philo->data->finished_lock);
	pthread_mutex_unlock(&philo->data->lock);
	return (dead);
}

bool	only_one(t_philo *philo)
{
	if (philo->data->nbr_philo == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		logs(philo, FORK);
		pthread_mutex_unlock(philo->right_fork);
		while (!is_dead(philo))
			;
		return (true);
	}
	return (false);
}

long	ft_atol(const char *nptr)
{
	int		sign;
	long	result;
	int		i;

	sign = 1;
	result = 0;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = (result * 10) + (nptr[i] - 48);
		i++;
	}
	return (result * sign);
}
