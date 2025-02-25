/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:46:02 by wacista           #+#    #+#             */
/*   Updated: 2025/02/24 19:46:03 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	simulation_status(t_params *table)
{
	pthread_mutex_lock(&table->stop_mutex);
	if (table->sim_stop == true)
	{
		pthread_mutex_unlock(&table->stop_mutex);
		return (true);
	}
	pthread_mutex_unlock(&table->stop_mutex);
	return (false);
}

static void	update_sim_stop(t_params *table, bool state)
{
	pthread_mutex_lock(&table->stop_mutex);
	table->sim_stop = state;
	pthread_mutex_unlock(&table->stop_mutex);
}

static bool	kill_philo(t_philo *philo)
{
	time_t	time;

	time = get_time_in_ms();
	if ((time - philo->last_meal) >= philo->table->time_die)
	{
		update_sim_stop(philo->table, true);
		pthread_mutex_lock(&philo->table->print_mutex);
		print_status(philo, "died");
		pthread_mutex_unlock(&philo->table->print_mutex);
		pthread_mutex_unlock(&philo->meal_mutex);
		return (true);
	}
	return (false);
}

static bool	check_philos_states(t_params *table)
{
	int		i;
	bool	all_ate_enough;

	all_ate_enough = true;
	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_lock(&table->philos[i]->meal_mutex);
		if (kill_philo(table->philos[i]) == true)
			return (true);
		if (table->must_eat_count != -1)
			if (table->philos[i]->times_ate \
			< (unsigned int)table->must_eat_count)
				all_ate_enough = false;
		pthread_mutex_unlock(&table->philos[i]->meal_mutex);
		i++;
	}
	if (table->must_eat_count != -1 && all_ate_enough == true)
	{
		update_sim_stop(table, true);
		return (true);
	}
	return (false);
}

void	*supervisor(void *data)
{
	t_params	*table;

	table = (t_params *)data;
	if (table->must_eat_count == 0)
		return (NULL);
	update_sim_stop(table, false);
	sim_start_delay(table->start_time);
	while (1)
	{
		if (check_philos_states(table))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
