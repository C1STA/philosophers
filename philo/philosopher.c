/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 04:39:30 by wcista            #+#    #+#             */
/*   Updated: 2023/03/06 07:55:38 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_is_alone(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
	write_status(philo, false, TOOK_FORK_1);
	philo_sleeping(philo->table, philo->table->time_to_die);
	write_status(philo, false, DIED);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[0]]);
	return (NULL);
}

static void	philo_thinking(t_philo *philo, bool silent)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->meal_time_lock);
	time_to_think = (philo->table->time_to_die \
	- (get_time_in_ms() - philo->last_meal) \
	- philo->table->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->meal_time_lock);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && silent == true)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (silent == false)
		write_status(philo, false, THINKING);
	philo_sleeping(philo->table, time_to_think);
}

static void	routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
	write_status(philo, false, TOOK_FORK_1);
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[1]]);
	write_status(philo, false, TOOK_FORK_2);
	write_status(philo, false, EATING);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->meal_time_lock);
	philo_sleeping(philo->table, philo->table->time_to_eat);
	if (!simulation_status(philo->table))
	{
		pthread_mutex_lock(&philo->meal_time_lock);
		philo->times_ate += 1;
		pthread_mutex_unlock(&philo->meal_time_lock);
	}
	write_status(philo, false, SLEEPING);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[1]]);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[0]]);
	philo_sleeping(philo->table, philo->table->time_to_sleep);
}

void	*philosopher(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->table->must_eat_count == 0)
		return (NULL);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = philo->table->start_time;
	pthread_mutex_unlock(&philo->meal_time_lock);
	sim_start_delay(philo->table->start_time);
	if (!philo->table->time_to_die)
		return (NULL);
	if (philo->table->nb_philos == 1)
		return (philo_is_alone(philo));
	else if (philo->id % 2)
		philo_thinking(philo, true);
	while (simulation_status(philo->table) == false)
	{
		routine(philo);
		philo_thinking(philo, false);
	}
	return (NULL);
}
