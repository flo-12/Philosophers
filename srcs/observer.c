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

#include "../includes/philo.h"

/* set_stop_sim:
*	Sets the value whether the simulation should stop
*	Precondition: mutex_stop_sim is locked.
*	No return.
*/
void	set_stop_sim(bool *stop_sim, bool state)
{
	*stop_sim = state;
}

/* get_stop_sim:
*	Checks if the simulation should be stopped and also
*	locks the mutex that protects the value.
*	Returns the bool-value whether the simulation should
*	stop.
*/
bool	get_stop_sim(bool *stop_sim, pthread_mutex_t *mutex_stop_sim)
{
	bool	state;

	state = false;
	pthread_mutex_lock(mutex_stop_sim);
	if (*stop_sim)
		state = true;
	return (state);
}

/* min_meals_reached:
*	Check if all philosophers had enough meals. If that's the
*	case, print out the state message (if in debug-mode) and
*	set the gen_info->sim_stop variable.
*	Return true if all philosophers had enough meals and false
*	if at least one philosophers didn't have n_min_meals.
*/
bool	min_meals_reached(t_observer *observer)
{
	int		i;

	if (observer->n_min_meals == -1)
		return (false);
	i = -1;
	while (++i < observer->n_philos)
	{
		pthread_mutex_lock(&observer->mutexes->mutex_meals[i]);
		if (observer->gen_info->n_meals[i]
			< (unsigned int)observer->n_min_meals)
		{
			pthread_mutex_unlock(&observer->mutexes->mutex_meals[i]);
			return (false);
		}
		pthread_mutex_unlock(&observer->mutexes->mutex_meals[i]);
	}
	pthread_mutex_lock(&observer->mutexes->mutex_stop_sim);
	set_stop_sim(&observer->gen_info->stop_sim, true);
	if (DEBUG_MSG)
		printf(STR_STATE_MEA, get_time_ms() - observer->t_start);
	pthread_mutex_unlock(&observer->mutexes->mutex_stop_sim);
	return (true);
}

/* pihlo_starved:
*	Check if one of the philosophers starved by comparing the
*	current time, the time of the last meal and the time to
*	die.
*	Sets the gen_info->stop_sim to true if a philisopher died
*	and triggers the state message.
*	Return true if a philosopher died and false if all
*	philosophers are still alive.
*/
bool	pihlo_starved(t_observer *observer)
{
	int	i;

	i = -1;
	while (++i < observer->n_philos)
	{
		pthread_mutex_lock(&observer->mutexes->mutex_meals[i]);
		if (!(get_time_ms() - observer->gen_info->t_last_meal[i]
				< observer->time_to_die))
		{
			pthread_mutex_unlock(&observer->mutexes->mutex_meals[i]);
			pthread_mutex_lock(&observer->mutexes->mutex_stop_sim);
			set_stop_sim(&observer->gen_info->stop_sim, true);
			printf(STR_STATE_DIE, get_time_ms() - observer->t_start, i + 1);
			pthread_mutex_unlock(&observer->mutexes->mutex_stop_sim);
			return (true);
		}
		pthread_mutex_unlock(&observer->mutexes->mutex_meals[i]);
	}
	return (false);
}

/* observer:
*	Monitors the table / if the simulation should stop. The
*	simulation should stop, if a philosopher died or if all
*	philosophers ate enough.
*	Sets the variable gen_info->stop_sim to true if the
*	simulation should stop to indicate the philosophers to
*	exit their functions.
*/
void	*observer(void *arg)
{
	t_observer	*observer;

	observer = (t_observer *)arg;
	time_sync(observer->t_start);
	while (1)
	{
		if (min_meals_reached(observer))
			break ;
		if (pihlo_starved(observer))
			break ;
	}
	return (NULL);
}
