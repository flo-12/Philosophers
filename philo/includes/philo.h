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

# define MAX_PHILOS 65536
# define STR_MAX_PHILOS "65536"
# define STR_MAX_U_INT "4294967295"

# define STR_ERR_USAGE	"usage: ./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n"
# define STR_ERR_INPUT_DIGIT	"invalid input (%s): \
not a valid unsigned integer between 0 and 4,294,967,295.\n"
# define STR_ERR_INPUT_MAXPHILOS	"invalid input (%s): \
too many Philosophers (max: %s).\n"
# define STR_ERR_THREAD	"error: Could not create thread.\n"
# define STR_ERR_MALLOC	"error: Could not allocate memory.\n"
# define STR_ERR_MUTEX	"error: Could not create mutex.\n"

# define STR_STATE_FOR "%llu %u has taken a fork\n"
# define STR_STATE_EAT "%llu %u is eating\n"
# define STR_STATE_SLE "%llu %u is sleeping\n"
# define STR_STATE_THI "%llu %u is thinking\n"
# define STR_STATE_DIE "%llu %u died\n"

/**************************************************************************
*                               STRUCTURES                                *
**************************************************************************/

typedef enum e_bool
{
	false = 0,
	true = 1
}	bool;

typedef struct s_table	t_table;

typedef struct s_philo
{
	pthread_t			thread;
	unsigned int		id;
	unsigned int		n_meals;
	unsigned long long	t_last_meal;
	t_table				*table;
}	t_philo;

typedef struct s_table
{
	unsigned long long	t_start;
	unsigned int		n_philos;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	unsigned int		n_min_meals;
	bool				died;
	t_philo				**philos;
}	t_table;

/**************************************************************************
*                               FUNCTIONS                                 *
**************************************************************************/

// exit_philo.c
void	error_free(char *str, char *arg1, char *arg2, t_table *table);

// output.c
void	msg(char *str, char *arg1, char *arg2);

// init.c
t_table	*init_table(int argc, char **argv);

// check_input.c
bool	is_valid_input(int argc, char **argv);

// utils.c
int		ft_strlen(char *str);

#endif
