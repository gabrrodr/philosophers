/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:51:17 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/10/19 15:35:41 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_forks(t_data *data, int i)
{
	while (i < (data->nbr_philo - 1))
	{
		if (i % 2)
		{
			data->philos[i].left_fork = &data->forks[i - 1];
			data->philos[i].right_fork = &data->forks[i];
		}
		else
		{
			data->philos[i].left_fork = &data->forks[i];
			data->philos[i].right_fork = &data->forks[i + 1];
		}
		i++;
	}
	if (i % 2)
	{
		data->philos[i].left_fork = &data->forks[i - 1];
		data->philos[i].right_fork = &data->forks[i];
	}
	else
	{
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[0];
	}
}

static void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].status = -1;
		data->philos[i].full = false;
		data->philos[i].meals = 0;
		data->philos[i].time_to_die = data->death_time;
		pthread_mutex_init(&data->philos[i].lock, NULL);
		i++;
	}
	init_forks(data, 0);
}

static t_data	*init_threads(t_data *data)
{
	int	i;

	i = 0;
	data->finished = false;
	data->table = malloc(sizeof(pthread_t) * data->nbr_philo);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_philo);
	if (!data->table || !data->forks)
		return (NULL);
	pthread_mutex_init(&data->lock, NULL);
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->finished_lock, NULL);
	while (i < data->nbr_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (data);
}

t_data	*init_data(t_data *data, int argc, char **argv)
{
	data->nbr_philo = atoi(argv[1]);
	data->death_time = ft_atol(argv[2]);
	data->eat_time = ft_atol(argv[3]);
	data->sleep_time = ft_atol(argv[4]);
	if (argc == 6)
		data->nbr_meals = atoi(argv[5]);
	else
		data->nbr_meals = 0;
	if (!data->nbr_philo || !data->death_time
		|| !data->eat_time || !data->sleep_time)
	{
		free(data);
		return (NULL);
	}
	data->start_time = 0;
	data->philos_full = 0;
	data->philos = malloc(data->nbr_philo * sizeof(t_philo));
	if (!data->philos)
		return (NULL);
	return (data);
}

t_data	*init(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data = init_data(data, argc, argv);
	if (!data)
		return (NULL);
	data = init_threads(data);
	if (!data)
		return (NULL);
	init_philos(data);
	return (data);
}
