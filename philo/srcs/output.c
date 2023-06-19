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

#include "philo.h"

/* msg:
*	Prints out the message in the argument str, where
*	arg1 and arg2 (if exist) are the arguments for printf.
*/
void	msg(char *str, char *arg1, char *arg2)
{
	if (!arg1)
		printf("%s", str);
	else if (!arg2)
		printf(str, arg1);
	else
		printf(str, arg1, arg2);
}

/* print_state:
*	Prints the state with the status message in str and using
*	a mutex_lock/unlock to access the t_start variable.
*/
void	print_state(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->table->mutex_time);
	printf(str, get_time_ms() - philo->table->t_start, philo->id);
	pthread_mutex_unlock(&philo->table->mutex_time);
}
