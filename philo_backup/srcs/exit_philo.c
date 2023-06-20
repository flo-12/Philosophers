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

#include "philo.h"

/* error_null:
*	Frees the data of table and prints out the message in str.
*/
/*void	error_free(char *str, char *arg1, char *arg2, t_table *table)
{
	if (table != NULL)
		free_table(table);
	msg(str, arg1, arg2);
}*/

/* free_mem:
*	Frees all the allocated memory in t_table and t_philo
*	if it exists.
*/
void	free_mem(t_table *table)
{
	int	i;

	if (!table)
		return ;
	if (table->philos)
	{
		i = -1;
		while (table->philos[++i])
			free(table->philos[i]);
		free(table->philos);
	}
	if (table->forks)
		free(table->forks);
	free(table);
}

/* destroy_mutex:
*	Destroys all the mutexes in table.
*/
void	destroy_mutex(t_table *table)
{
	int	i;

	pthread_mutex_destroy(&table->mutex_stop_sim);
	pthread_mutex_destroy(&table->mutex_time);
	pthread_mutex_destroy(&table->mutex_print);
	pthread_mutex_destroy(&table->forks)
	i = -1;
	while (++i < table->n_philos)
		pthread_mutex_destroy(&table->forks[i]);
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
	if (n_detach == -1)
	{
		if (pthread_detach(table->observer))
			error = true;
		n_detach = table->n_philos;
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
		// print STR_ERR_THREAD_DET
}

/* exit_philo:
*	Free the allocated memory in the table & philo structs.
*
*	Detaches the threads in t_philos and the observer - 
*	concerning the n_detach variable.
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
	destroy_mutex(table);
	detach_thread(n_detach, table);
	free_mem(table);
}
