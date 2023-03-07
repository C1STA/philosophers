/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 04:29:48 by wcista            #+#    #+#             */
/*   Updated: 2023/03/06 07:31:56 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	start_simulation(t_params *table)
{
	int	i;

	table->start_time = get_time_in_ms() + (table->nb_philos * 2 * 10);
	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_create(&table->philos[i]->thread, NULL, \
		&philosopher, table->philos[i]))
			return (error_bool(THREAD_CREAT_ERR, table));
		i++;
	}
	if (pthread_create(&table->grim_reaper, NULL, &grim_reaper, table))
		return (error_bool(THREAD_CREAT_ERR, table));
	return (true);
}

bool	stop_simulation(t_params *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_join(table->philos[i]->thread, NULL))
			return (error_bool(THREAD_JOIN_ERR, table));
		i++;
	}
	if (table->nb_philos > 1)
		if (pthread_join(table->grim_reaper, NULL))
			return (error_bool(THREAD_JOIN_ERR, table));
	if (!destroy_mutexes(table))
		return (false);
	free_prog(table);
	return (true);
}
