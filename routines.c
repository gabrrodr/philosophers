/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:50:50 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/10/19 15:36:32 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_time(t_philo *philo, uint64_t time)
{
	if ((get_time() + time) >= philo->time_to_die)
		usleep((philo->time_to_die - get_time()) * 1000);
	else
		usleep(time * 1000);
}

void	thinking(t_philo *philo)
{
	if (!is_dead(philo) && philo->status != THINKING)
	{
		philo->status = THINKING;
		logs(philo, philo->status);
		wait_time(philo, 5);
	}
}

void	*routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	pthread_mutex_lock(&philo->lock);
	philo->time_to_die = philo->data->start_time + philo->data->death_time;
	pthread_mutex_unlock(&philo->lock);
	if (philo->id % 2 == 0 || philo->id == philo->data->nbr_philo)
	{
		thinking(philo);
	}
	if (only_one(philo))
	{
		return (NULL);
	}
	while (!is_dead(philo))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
