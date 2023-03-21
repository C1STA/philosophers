/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 03:31:23 by wcista            #+#    #+#             */
/*   Updated: 2023/03/21 13:31:59 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	destroy_mutexes(t_params *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_mutex_destroy(&table->fork_mutex[i]))
			return (error_bool(MUTEX_DEST_ERR, table));
		if (pthread_mutex_destroy(&table->philos[i]->meal_mutex))
			return (error_bool(MUTEX_DEST_ERR, table));
		i++;
	}
	if (pthread_mutex_destroy(&table->print_mutex))
		return (error_bool(MUTEX_DEST_ERR, table));
	if (pthread_mutex_destroy(&table->stop_mutex))
		return (error_bool(MUTEX_DEST_ERR, table));
	return (true);
}

static void	*free_philos(t_params *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		if (table->philos[i] != NULL)
		{
			free(table->philos[i]);
			table->philos[i] = NULL;
		}
		i++;
	}
	free(table->philos);
	table->philos = NULL;
	return (NULL);
}

void	*free_prog(t_params *table)
{
	if (!table)
		return (NULL);
	if (table->fork_mutex != NULL)
	{
		free(table->fork_mutex);
		table->fork_mutex = NULL;
	}
	if (table->philos != NULL)
		free_philos(table);
	free(table);
	table = NULL;
	return (NULL);
}

void	*error_null(char *str, t_params *table)
{
	if (table != NULL)
		free_prog(table);
	msg(str, 0);
	return (NULL);
}

bool	error_bool(char *str, t_params *table)
{
	if (table != NULL)
		free_prog(table);
	return (msg(str, false));
}
