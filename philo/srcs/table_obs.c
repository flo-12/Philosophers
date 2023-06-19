/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_obs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:37:23 by fbecht            #+#    #+#             */
/*   Updated: 2023/06/19 12:37:25 by fbecht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* set_stop_sim:
*	Sets the value whether the simulation should stop
*	and locks the mutex that protects the value.
*/
void	set_stop_sim(t_table *table, bool state)
{
	pthread_mutex_lock(&table->mutex_stop_sim);
	table->stop_sim = state;
	pthread_mutex_unlock(&table->mutex_stop_sim);
}

/* get_stop_sim:
*	Checks if the simulation should be stopped and also
*	locks the mutex that protects the value.
*	Returns the bool-value whether the simulation should
*	stop.
*/
bool	get_stop_sim(t_table *table)
{
	bool	state;

	state = false;
	pthread_mutex_lock(&table->mutex_stop_sim);
	if (table->stop_sim)
		state = true;
	pthread_mutex_unlock(&table->mutex_stop_sim);
	return (state);
}
