/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:35:32 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/10/19 15:29:48 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_data(t_data *data)
{
	int	i;

	i = -1;
	if (!data)
		return ;
	while (++i < data->nbr_philo)
	{
		pthread_mutex_destroy(&data->philos[i].lock);
		pthread_mutex_destroy(&data->forks[i]);
	}
	pthread_mutex_destroy(&data->lock);
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->finished_lock);
	if (data->table)
		free(data->table);
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
	free(data);
}
