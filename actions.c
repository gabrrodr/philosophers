/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:35:40 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/10/19 15:26:38 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_philo *philo)
{
	if (!is_dead(philo) && philo->status != SLEEPING)
	{
		philo->status = SLEEPING;
		logs(philo, philo->status);
		wait_time(philo, philo->data->sleep_time);
	}
}

static bool	get_left_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (false);
	}
	logs(philo, FORK);
	return (true);
}

static bool	get_right_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		return (false);
	}
	logs(philo, FORK);
	return (true);
}

static bool	get_forks(t_philo *philo)
{
	if (!get_left_fork(philo))
		return (false);
	if (!get_right_fork(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (false);
	}
	return (true);
}

void	eating(t_philo *philo)
{
	if (!get_forks(philo))
		return ;
	pthread_mutex_lock(&philo->lock);
	philo->time_to_die = get_time() + philo->data->death_time;
	pthread_mutex_unlock(&philo->lock);
	philo->status = EATING;
	logs(philo, philo->status);
	philo->meals++;
	wait_time(philo, philo->data->eat_time);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
