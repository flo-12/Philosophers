/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:53:43 by fbecht            #+#    #+#             */
/*   Updated: 2023/06/15 15:53:45 by fbecht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* free_mem:
*	Frees all the allocated memory in the structs.
*/
void	free_mem(t_table *table)
{
	int	i;

	if (!table)
		return ;
	i = -1;
	while (table->philos && ++i < table->n_philos)
		free(table->philos[i]);
	if (table->philos)
		free(table->philos);
	if (table->observer)
		free(table->observer);
	if (table->mutexes && table->mutexes->forks)
		free(table->mutexes->forks);
	if (table->mutexes && table->mutexes->mutex_meals)
		free(table->mutexes->mutex_meals);
	if (table->mutexes)
		free(table->mutexes);
	if (table->gen_info && table->gen_info->n_meals)
		free(table->gen_info->n_meals);
	if (table->gen_info && table->gen_info->t_last_meal)
		free(table->gen_info->t_last_meal);
	if (table->gen_info)
		free(table->gen_info);
	free(table);
}

/* destroy_mutex:
*	Destroys all the mutexes in table.
*/
void	destroy_mutex(t_mutex *mutexes, int n_philos)
{
	int	i;

	pthread_mutex_destroy(&mutexes->mutex_stop_sim);
	pthread_mutex_destroy(&mutexes->mutex_time);
	pthread_mutex_destroy(&mutexes->mutex_print);
	i = -1;
	while (++i < n_philos)
	{
		pthread_mutex_destroy(&mutexes->forks[i]);
		pthread_mutex_destroy(&mutexes->mutex_meals[i]);
	}
}

/* detach_thread:
*	Detaches the threads in table->philo[n]->thread and
*	table->observer.
*	If n_detach is between 0..(n_philos-1), only the thread
*	of the 0..n_detach philos will be detached and the
*	thread_observer is only detached if n_detach = n_philos.
*	In all other cases, nothing is detached.
*/
void	detach_thread(int n_detach, t_table *table)
{
	int		i;
	bool	error;

	error = false;
	if (n_detach == table->n_philos)
	{
		if (pthread_detach(table->observer->thread))
			error = true;
	}
	else if (n_detach >= 0 && n_detach < table->n_philos)
		n_detach++;
	else
		return ;
	i = -1;
	while (++i < n_detach)
	{
		if (pthread_detach(table->philos[i]->thread))
			error = true;
	}
	if (error)
		msg(STR_ERR_THREAD_DET, NULL);
}

/* exit_philo:
*	Free the allocated memory in the table & philo structs.
*
*	Detaches the threads in t_philos and the observer - 
*	concerning the n_detach variable. After pthread_join, the
*	threads shouldn't be detached anymore, because pthread_join
*	already detaches the threads.
*
*	Destroys all the mutexes (no additional check whether it's
*	initialized or locked needed).
*
*	In order the function
*		1) destroys mutexes
*		2) detaches threads
*		3) frees memory
*	to avoid to lose any pointers (to threads & mutexes).
*/
void	exit_philo(int n_detach, t_table *table, char *str, char *arg)
{
	destroy_mutex(table->mutexes, table->n_philos);
	detach_thread(n_detach, table);
	free_mem(table);
	msg(str, arg);
}
