/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:38:15 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/10/19 15:39:33 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
	{
		printf("Error: gettimeofday() not 0");
		return (0);
	}
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

static int	dining(t_data *data)
{
	int	n;

	data->start_time = get_time();
	if (data->sleep_time == 0)
		return (1);
	pthread_mutex_lock(&data->lock);
	n = 0;
	while (n < data->nbr_philo)
	{
		if (pthread_create(&data->table[n], NULL, &routine, &data->philos[n]))
			return (1);
		n++;
	}
	pthread_mutex_unlock(&data->lock);
	n = 0;
	while (n < data->nbr_philo)
	{
		if (pthread_join(data->table[n], NULL))
			return (1);
		n++;
	}
	return (0);
}

int	check_input(char **argv)
{
	int			i;
	int			j;
	long		tmp;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (argv[i][j] == '-')
				return (1);
			if (argv[i][j] == '+')
				j++;
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
		}
		tmp = ft_atol(argv[i]);
		if (tmp < 0 || tmp > 4294967295)
			return (1);
	}
	if (argv[2][0] == '0' && !argv[2][1])
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if ((argc != 5 && argc != 6) || check_input(argv))
	{
		printf("Invalid Arguments\n");
		return (0);
	}
	data = init(argc, argv);
	if (!data)
	{
		free_data(data);
		return (1);
	}
	dining(data);
	free_data(data);
}
