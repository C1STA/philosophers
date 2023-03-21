/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 04:39:30 by wcista            #+#    #+#             */
/*   Updated: 2023/03/21 13:31:59 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_is_alone(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_mutex[philo->fork[0]]);
	display_status(philo, TOOK_FORK);
	usleep(philo->table->time_die * 1000);
	pthread_mutex_unlock(&philo->table->fork_mutex[philo->fork[0]]);
	print_status(philo, "died");
	return (NULL);
}

static bool	philo_thinking(t_philo *philo)
{
	display_status(philo, THINKING);
	usleep(philo->table->time_think * 1000);
	if (philo->times_ate == (unsigned int)philo->table->must_eat_count)
		return (false);
	return (true);
}

static void	eat_and_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_mutex[philo->fork[0]]);
	display_status(philo, TOOK_FORK);
	pthread_mutex_lock(&philo->table->fork_mutex[philo->fork[1]]);
	display_status(philo, TOOK_FORK);
	display_status(philo, EATING);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->meal_mutex);
	latency(philo->table, philo->table->time_eat);
	if (!simulation_status(philo->table))
	{
		pthread_mutex_lock(&philo->meal_mutex);
		philo->times_ate++;
		pthread_mutex_unlock(&philo->meal_mutex);
	}
	pthread_mutex_unlock(&philo->table->fork_mutex[philo->fork[1]]);
	pthread_mutex_unlock(&philo->table->fork_mutex[philo->fork[0]]);
	display_status(philo, SLEEPING);
	latency(philo->table, philo->table->time_sleep);
}

void	*philosopher(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->table->must_eat_count == 0)
		return (NULL);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = philo->table->start_time;
	pthread_mutex_unlock(&philo->meal_mutex);
	sim_start_delay(philo->table->start_time);
	if (!philo->table->time_die)
		return (NULL);
	if (philo->table->nb_philos == 1)
		return (philo_is_alone(philo));
	if (philo->id % 2)
		usleep(philo->table->time_think * 1000);
	while (simulation_status(philo->table) == false)
	{
		eat_and_sleep(philo);
		if (!philo_thinking(philo))
			return (NULL);
	}
	return (NULL);
}
