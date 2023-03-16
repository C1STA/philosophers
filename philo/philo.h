/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:52:20 by wcista            #+#    #+#             */
/*   Updated: 2023/03/16 11:10:08 by wcista           ###   ########.fr       */
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
	time_t			start_time;
	int				nb_philos;
	pthread_t		grim_reaper;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				must_eat_count;
	bool			sim_stop;
	pthread_mutex_t	sim_stop_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*fork_locks;
	t_philo			**philos;
}	t_params;

typedef struct s_philo
{
	pthread_t		thread;
	unsigned int	id;
	unsigned int	times_ate;
	unsigned int	fork[2];
	pthread_mutex_t	meal_time_lock;
	time_t			last_meal;
	t_params		*table;
}	t_philo;

typedef enum e_status
{
	DIED,
	EATING,
	SLEEPING,
	THINKING,
	TOOK_FORK_1,
	TOOK_FORK_2,
}	t_status;

//	exit.c
bool	destroy_mutexes(t_params *table);
void	*free_prog(t_params *table);
bool	error_bool(char *str, t_params *table);
void	*error_null(char *str, t_params *table);

//	grim_reaper.c
bool	simulation_status(t_params *table);
void	*grim_reaper(void *data);

//	init.c
bool	init_params(t_params *table, int ac, char *av[]);

//	lib.c
int		ft_atoi(char *str);
int		ft_strlen(char *str);

//output.c
bool	msg(char *str, bool exit_nb);
bool	msg_max_philos(char *str, int max, bool exit_nb);
void	write_status(t_philo *philo, bool reaper_report, t_status status);

//philo.c
void	*philosopher(void *data);

//sim.c
bool	start_simulation(t_params *table);
bool	stop_simulation(t_params *table);

//time.c
time_t	get_time_in_ms(void);
void	sim_start_delay(time_t start_time);
void	philo_sleeping(t_params *table, time_t sleep_time);

#endif
