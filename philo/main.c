/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:45:47 by wacista           #+#    #+#             */
/*   Updated: 2025/02/24 19:45:48 by wacista          ###   ########.fr       */
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
