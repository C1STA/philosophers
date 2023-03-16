/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 03:49:25 by wcista            #+#    #+#             */
/*   Updated: 2023/03/16 11:02:42 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	init_forks_and_mutexes(t_params *table)
{
	int	i;

	table->fork_locks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
	* table->nb_philos);
	if (!table->fork_locks)
		return (error_bool(MALLOC_ERR, table));
	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_mutex_init(&table->fork_locks[i], 0))
			return (error_bool(MUTEX_INIT_ERR, table));
		i++;
	}
	if (pthread_mutex_init(&table->sim_stop_lock, 0))
		return (error_bool(MUTEX_INIT_ERR, table));
	if (pthread_mutex_init(&table->write_lock, 0))
		return (error_bool(MUTEX_INIT_ERR, table));
	return (true);
}

static void	grant_forks(t_philo *philo)
{
	unsigned int	left_fork;
	unsigned int	right_fork;
	unsigned int	temp;

	left_fork = philo->id;
	right_fork = (philo->id + 1) % philo->table->nb_philos;
	if (philo->id % 2)
	{
		temp = left_fork;
		left_fork = right_fork;
		right_fork = temp;
	}
	philo->fork[0] = left_fork;
	philo->fork[1] = right_fork;
}

static t_philo	**init_philos(t_params *table)
{
	t_philo	**philos;
	int		i;

	philos = (t_philo **)malloc(sizeof(t_philo) * table->nb_philos);
	if (!philos)
		return (error_null(MALLOC_ERR, table));
	memset(philos, 0, sizeof(t_philo));
	i = 0;
	while (i < table->nb_philos)
	{
		philos[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!philos[i])
			return (error_null(MALLOC_ERR, table));
		memset(philos[i], 0, sizeof(t_philo));
		if (pthread_mutex_init(&philos[i]->meal_time_lock, 0))
			return (error_null(MUTEX_INIT_ERR, table));
		philos[i]->table = table;
		philos[i]->id = i;
		philos[i]->times_ate = 0;
		grant_forks(philos[i]);
		i++;
	}
	return (philos);
}

static bool	check_params(int ac, char *av[], t_params *table)
{
	bool	is_valid;

	is_valid = true;
	if (table->nb_philos <= 0)
		is_valid = msg(ARG_1_ERR, false);
	if (table->nb_philos > MAX_PHILOS)
		is_valid = msg_max_philos(MAX_PHILOS_ERR, MAX_PHILOS, false);
	if (table->time_to_die < 0)
		is_valid = msg(ARG_2_ERR, false);
	if (table->time_to_eat < 0)
		is_valid = msg(ARG_3_ERR, false);
	if (table->time_to_sleep < 0)
		is_valid = msg(ARG_4_ERR, false);
	if (ac == 6)
	{
		table->must_eat_count = ft_atoi(av[5]);
		if (table->must_eat_count < 0)
			is_valid = msg(ARG_5_ERR, false);
	}
	else
		table->must_eat_count = -1;
	if (!is_valid)
		free_prog(table);
	return (is_valid);
}

bool	init_params(t_params *table, int ac, char *av[])
{
	table->nb_philos = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (!check_params(ac, av, table))
		return (false);
	table->philos = init_philos(table);
	if (!table->philos)
		return (false);
	if (!init_forks_and_mutexes(table))
		return (false);
	table->sim_stop = false;
	return (true);
}
