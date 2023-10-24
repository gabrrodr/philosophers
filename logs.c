/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:21:17 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/10/19 15:36:09 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	logs(t_philo *p, int status)
{
	pthread_mutex_lock(&p->data->write);
	if (status == DEAD)
		printf("%lu %d died\n", get_time() - p->data->start_time, p->id);
	else if (status == EATING)
		printf("%lu %d is eating\n", get_time() - p->data->start_time, p->id);
	else if (status == THINKING)
		printf("%lu %d is thinking\n", get_time() - p->data->start_time, p->id);
	else if (status == SLEEPING)
		printf("%lu %d is sleeping\n", get_time() - p->data->start_time, p->id);
	else if (status == FORK)
		printf("%lu %d has taken a fork\n",
			get_time() - p->data->start_time, p->id);
	pthread_mutex_unlock(&p->data->write);
}
