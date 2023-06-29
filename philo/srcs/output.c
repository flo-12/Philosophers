/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:22:09 by fbecht            #+#    #+#             */
/*   Updated: 2023/06/15 13:22:12 by fbecht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* msg:
*	Prints out the message in the argument str, where
*	arg1 and arg2 (if exist) are the arguments for printf.
*/
void	msg(char *str, char *arg1)
{
	if (str && !arg1)
		printf("%s", str);
	else if (str && arg1)
		printf(str, arg1);
}

/* print_state:
*	Prints the state with the status message in str and using
*	a mutex_lock/unlock to access the t_start variable.
*	Only prints out the state if the simulation shouldn't be
*	stopped.
*/
void	print_state(char *str, t_philo *philo)
{
	if (!get_stop_sim(&philo->gen_info->stop_sim,
			&philo->mutexes->mutex_stop_sim))
		printf(str, get_time_ms() - philo->t_start, philo->id + 1);
	pthread_mutex_unlock(&philo->mutexes->mutex_stop_sim);
}
