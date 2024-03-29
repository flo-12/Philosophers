/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:45:28 by fbecht            #+#    #+#             */
/*   Updated: 2023/06/13 12:45:30 by fbecht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/**************************************************************************
*                               HEADERS                                   *
**************************************************************************/

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

/******************************************************************************
*                                     Macros                                  *
******************************************************************************/

# define DEBUG_MSG 0
# define START_DELAY 100
# define SLEEP_TIME_CHECK 5000
# define MAX_PHILOS 300
# define STR_MAX_PHILOS "300"
# define STR_MAX_U_INT "4294967295"
# define STR_MAX_INT "2147483647"

# define STR_ERR_USAGE	"usage: ./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n"
# define STR_ERR_INPUT_DIGIT	"invalid input (%s): \
not a valid number - either out of range or contains \
non-numeric characters.\n"
# define STR_ERR_INPUT_MAXPHILOS	"invalid input (%s): \
too many Philosophers (max: %s).\n"
# define STR_ERR_ZERO	"0 as an input or an empty string is not allowed.\n"
# define STR_ERR_THREAD	"error: Could not create thread.\n"
# define STR_ERR_THREAD_DET	"error exiting philo.c: Could not detach thread.\n"
# define STR_ERR_MALLOC	"error: Could not allocate memory.\n"
# define STR_ERR_MUTEX	"error: Could not create mutex.\n"

# define STR_SUC_0MEAL "number_of_times_each_philosopher_must_eat = 0 \
=> simulation is done before it started :)\n"

# define STR_STATE_FOR "%llu %u has taken a fork\n"
# define STR_STATE_EAT "%llu %u is eating\n"
# define STR_STATE_SLE "%llu %u is sleeping\n"
# define STR_STATE_THI "%llu %u is thinking\n"
# define STR_STATE_DIE "%llu %u died\n"
# define STR_STATE_MEA "%llu all philosopher ate enough\n"

/**************************************************************************
*                               STRUCTURES                                *
**************************************************************************/

typedef struct gen_info
{
	unsigned int		*n_meals;
	unsigned long long	*t_last_meal;
	bool				stop_sim;
}	t_gen_info;

typedef struct s_mutex
{
	pthread_mutex_t		mutex_stop_sim;
	pthread_mutex_t		*mutex_meals;
	pthread_mutex_t		mutex_time;
	pthread_mutex_t		*forks;
}	t_mutex;

typedef struct s_philo
{
	pthread_t			thread;
	unsigned int		id;
	int					n_philos;
	unsigned int		n_meals;
	unsigned long long	t_last_meal;
	unsigned long long	t_start;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	unsigned long long	time_to_die;
	int					fork[2];
	t_gen_info			*gen_info;
	t_mutex				*mutexes;
}	t_philo;

typedef struct s_observer
{
	pthread_t			thread;
	int					n_philos;
	int					n_min_meals;
	unsigned long long	t_start;
	unsigned long long	time_to_die;
	t_mutex				*mutexes;
	t_gen_info			*gen_info;
}	t_observer;

typedef struct s_table
{
	unsigned long long	t_start;
	int					n_philos;
	t_observer			*observer;
	t_mutex				*mutexes;
	t_philo				**philos;
	t_gen_info			*gen_info;
}	t_table;

/**************************************************************************
*                               FUNCTIONS                                 *
**************************************************************************/

// check_input.c
bool				check_input(int argc, char **argv);

// exit_philo.c
void				exit_philo(int n_detach, t_table *table, 
						char *str, char *arg);
void				free_mem(t_table *table);

// init.c
bool				init_observer(t_table *table, int argc, char **argv);
bool				init_gen_info(t_table *table);
bool				init_mutexes(t_table *table);
bool				init_philos(t_table *table, char **argv);

// output.c
void				msg(char *str, char *arg1);
void				print_state(char *str, t_philo *philo);

// philosopher.c
void				*philosopher(void *arg);

// observer.c
bool				get_stop_sim(bool *stop_sim, 
						pthread_mutex_t *mutex_stop_sim);
void				*observer(void *arg);

// time.c
unsigned long long	get_time_ms(void);
void				time_sync(unsigned long long start_time);
void				set_start_time(t_table *table);
void				philo_wait(unsigned long long time_to_sleep,
						t_philo *philo);

// utils.c
int					ft_strlen(char *str);
unsigned int		atoi_uint(char *str);

#endif
