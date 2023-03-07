/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_reaper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 05:18:53 by wcista            #+#    #+#             */
/*   Updated: 2023/03/06 07:50:30 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	simulation_status(t_params *table)
{
	bool	status;

	status = false;
	pthread_mutex_lock(&table->sim_stop_lock);
	if (table->sim_stop == true)
		status = true;
	pthread_mutex_unlock(&table->sim_stop_lock);
	return (status);
}

static void	update_sim_stop(t_params *table, bool state)
{
	pthread_mutex_lock(&table->sim_stop_lock);
	table->sim_stop = state;
	pthread_mutex_unlock(&table->sim_stop_lock);
}

static bool	kill_philo(t_philo *philo)
{
	time_t	time;

	time = get_time_in_ms();
	if ((time - philo->last_meal) >= philo->table->time_to_die)
	{
		update_sim_stop(philo->table, true);
		write_status(philo, true, DIED);
		pthread_mutex_unlock(&philo->meal_time_lock);
		return (true);
	}
	return (false);
}

static bool	end_condition_reached(t_params *table)
{
	int		i;
	bool	all_ate_enough;

	all_ate_enough = true;
	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_lock(&table->philos[i]->meal_time_lock);
		if (kill_philo(table->philos[i]))
			return (true);
		if (table->must_eat_count != -1)
			if (table->philos[i]->times_ate \
			< (unsigned int)table->must_eat_count)
				all_ate_enough = false;
		pthread_mutex_unlock(&table->philos[i]->meal_time_lock);
		i++;
	}
	if (table->must_eat_count != -1 && all_ate_enough == true)
	{
		update_sim_stop(table, true);
		return (true);
	}
	return (false);
}

void	*grim_reaper(void *data)
{
	t_params	*table;

	table = (t_params *)data;
	if (table->must_eat_count == 0)
		return (NULL);
	update_sim_stop(table, false);
	sim_start_delay(table->start_time);
	while (true)
	{
		if (end_condition_reached(table) == true)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
