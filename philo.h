/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:30:31 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/10/19 15:32:03 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdint.h>
# include <stdbool.h>

enum e_actions{
	DEAD,
	EATING,
	SLEEPING,
	THINKING,
	FORK,
	FULL
};

//struct data specific to philos
typedef struct s_philo
{
	struct s_data	*data;
	int				id;
	int				status;
	bool			full;
	int				meals;
	uint64_t		time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}				t_philo;

//struct of the general data
typedef struct s_data
{
	pthread_t		*table;
	t_philo			*philos;
	int				nbr_philo;
	int				nbr_meals;
	int				philos_full;
	bool			finished;
	uint64_t		death_time;
	uint64_t		eat_time;
	uint64_t		sleep_time;
	uint64_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
	pthread_mutex_t	finished_lock;
}				t_data;

//first step, main
int			check_input(char **argv);

//routine
void		*routine(void *philo_ptr);

//init
t_data		*init(int argc, char **argv);

//wait time
void		wait_time(t_philo *philo, uint64_t time);

//utils
uint64_t	get_time(void);
bool		only_one(t_philo *philo);
int			is_dead(t_philo *philo);
void		logs(t_philo *p, int status);
long		ft_atol(const char *nptr);

//actions
void		eating(t_philo *philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);

//free
void		free_data(t_data *data);

#endif