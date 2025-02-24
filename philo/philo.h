/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:46:10 by wacista           #+#    #+#             */
/*   Updated: 2025/02/24 19:46:11 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <string.h>
# include <stdbool.h>
# include <sys/time.h>
# include <pthread.h>

# define MAX_PHILOS 200
# define ARGS_ERR "philo: wrong format: four or five arguments allowed\n"
# define ARG_1_ERR "philo: wrong format: <number of philosophers>\n"
# define ARG_2_ERR "philo: wrong format: <time_to_die>\n"
# define ARG_3_ERR "philo: wrong format: <time_to_eat>\n"
# define ARG_4_ERR "philo: wrong format: <time_to_sleep>\n"
# define ARG_5_ERR "philo: wrong format: \
<number_of_times_each_philosopher_must_eat>\n"
# define MAX_PHILOS_ERR "philo: <number of philosophers> > "
# define MALLOC_ERR "philo: malloc failed\n"
# define MUTEX_INIT_ERR "philo: pthread_mutex_init failed\n"
# define MUTEX_DEST_ERR "philo: pthread_mutex_destory failed\n"
# define THREAD_CREAT_ERR "philo: pthread_create failed\n"
# define THREAD_JOIN_ERR "philo: pthread_join failed\n"

typedef struct s_philo	t_philo;

typedef struct s_params
{
	int				nb_philos;
	time_t			time_die;
	time_t			time_eat;
	time_t			time_sleep;
	time_t			time_think;
	time_t			start_time;
	int				must_eat_count;
	bool			sim_stop;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	*fork_mutex;
	pthread_t		supervisor;
	t_philo			**philos;
}	t_params;

typedef struct s_philo
{
	pthread_t		thread;
	unsigned int	id;
	unsigned int	times_ate;
	unsigned int	fork[2];
	pthread_mutex_t	meal_mutex;
	time_t			last_meal;
	t_params		*table;
}	t_philo;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TOOK_FORK,
}	t_status;

//	exit.c
bool	destroy_mutexes(t_params *table);
void	*free_prog(t_params *table);
bool	error_bool(char *str, t_params *table);
void	*error_null(char *str, t_params *table);

//	supervisor.c
bool	simulation_status(t_params *table);
void	*supervisor(void *data);

//	init.c
bool	init_params(t_params *table, int ac, char *av[]);

//	lib.c
int		ft_atoi(char *str);
int		ft_strlen(char *str);

//output.c
bool	msg(char *str, bool exit_nb);
bool	msg_max_philos(char *str, int max, bool exit_nb);
void	print_status(t_philo *philo, char *str);
void	display_status(t_philo *philo, t_status status);

//philo.c
void	*philosopher(void *data);

//sim.c
bool	start_simulation(t_params *table);
bool	stop_simulation(t_params *table);

//time.c
time_t	get_time_in_ms(void);
void	sim_start_delay(time_t start_time);
void	latency(t_params *table, time_t sleep_time);

#endif
