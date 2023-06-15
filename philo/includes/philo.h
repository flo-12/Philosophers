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

# define STR_USAGE	"usage: ./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n"
# define STR_ERR_INPUT_DIGIT	"invalid input: \
not a valid unsigned integer between 0 and 4,294,967,295.\n"
# define STR_ERR_THREAD	"error: Could not create thread.\n"
# define STR_ERR_MALLOC	"error: Could not allocate memory.\n"
# define STR_ERR_MUTEX	"error: Could not create mutex.\n"
# define STR_STATE_EAT "is eating"
# define STR_STATE_SLE "is sleeping"
# define STR_STATE_THI "is thinking"
# define STR_STATE_DIE "died"

/**************************************************************************
*                               STRUCTURES                                *
**************************************************************************/

/**************************************************************************
*                               FUNCTIONS                                 *
**************************************************************************/


#endif
