/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 05:05:47 by wcista            #+#    #+#             */
/*   Updated: 2023/03/21 12:48:57 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putnbr(int n)
{
	char	c;

	if (n < 10)
	{
		c = n + '0';
		write (2, &c, 1);
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
}

bool	msg_max_philos(char *str, int max, bool exit_nb)
{
	write(2, str, ft_strlen(str));
	ft_putnbr(max);
	write(2, "\n", 1);
	return (exit_nb);
}

bool	msg(char *str, bool exit_nb)
{
	write(2, str, ft_strlen(str));
	return (exit_nb);
}

void	print_status(t_philo *philo, char *str)
{
	printf("%ld ", (get_time_in_ms() - philo->table->start_time));
	printf("%d ", (philo->id + 1));
	printf("%s\n", str);
}

void	display_status(t_philo *philo, t_status status)
{
	pthread_mutex_lock(&philo->table->print_mutex);
	if (simulation_status(philo->table) == true)
	{
		pthread_mutex_unlock(&philo->table->print_mutex);
		return ;
	}
	if (status == EATING)
		print_status(philo, "is eating");
	else if (status == SLEEPING)
		print_status(philo, "is sleeping");
	else if (status == THINKING)
		print_status(philo, "is thinking");
	else if (status == TOOK_FORK)
		print_status(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->table->print_mutex);
}
