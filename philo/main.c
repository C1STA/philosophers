/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:35:17 by wcista            #+#    #+#             */
/*   Updated: 2023/03/06 07:15:25 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	t_params	*table;

	if (ac != 5 && ac != 6)
		return (msg(ARGS_ERR, EXIT_FAILURE));
	table = (t_params *)malloc(sizeof(t_params));
	if (!table)
		return (msg(MALLOC_ERR, EXIT_FAILURE));
	memset(table, 0, sizeof(t_params));
	if (!init_params(table, ac, av))
		return (EXIT_FAILURE);
	if (!start_simulation(table))
		return (EXIT_FAILURE);
	if (!stop_simulation(table))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
