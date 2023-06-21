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

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

/******************************************************************************
*                                     Macros                                  *
******************************************************************************/

# define DEBUG_MSG 1
# define MAX_PHILOS 300
# define STR_MAX_PHILOS "300"
# define STR_MAX_U_INT "4294967295"

# define STR_ERR_USAGE	"usage: ./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n"
# define STR_ERR_INPUT_DIGIT	"invalid input (%s): \
not a valid unsigned integer between 0 and 4,294,967,295.\n"
# define STR_ERR_INPUT_MAXPHILOS	"invalid input (%s): \
too many Philosophers (max: %s).\n"
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

typedef enum e_bool
{
	false = 0,
	true = 1
}	bool;

typedef struct gen_info
{
	unsigned int		*n_meals;
	unsigned long long	*t_last_meal;
	bool				stop_sim;		// if philo is dead or all philos had enough meals
}	t_gen_info;

typedef struct s_mutex
{
	pthread_mutex_t		mutex_stop_sim;		// for stop_sim
	pthread_mutex_t		mutex_time;			// for t_start and t_last_meal
	pthread_mutex_t		mutex_print;		// to print state message (printf)
	pthread_mutex_t		*forks;
}	t_mutex;

typedef struct s_philo
{
	pthread_t			thread;
	unsigned int		id;
	unsigned int		n_meals;		// [obs] detect -> stop_sim
	unsigned long long	t_last_meal;	// [obs] detect starvation -> stop_sim
	unsigned long long	t_start;		// not initialized
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	int					fork[2];
	t_gen_info			*gen_info;
	t_mutex				*mutexes;
}	t_philo;

typedef struct s_observer
{
	pthread_t			thread;
	int					n_philos;
	int					n_min_meals;
	unsigned long long	t_start;		// not initialized
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
void				exit_philo(int n_detach, t_table *table, char *str, char *arg);
void				free_mem(t_table *table);

// init.c
t_table				*init_table(int argc, char **argv);

// output.c
void				msg(char *str, char *arg1);
void				print_state(char *str, unsigned long long t_start, int id, pthread_mutex_t *mutex_print);

// philosopher.c
void				*philosopher(void *arg);

// observer.c
bool				get_stop_sim(bool *stop_sim, pthread_mutex_t *mutex_stop_sim);
void				*observer(void *arg);

// time.c
unsigned long long	get_time(void);
void				set_start_time(t_table *table);

// utils.c
int					ft_strlen(char *str);
unsigned int		atoi_uint(char *str);

#endif
