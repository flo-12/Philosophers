/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:43:53 by fbecht            #+#    #+#             */
/*   Updated: 2023/06/15 13:43:55 by fbecht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* init_forks:
*	Initializes the index of the fork the philosopher graps. It
*	first graps the fork[0] and afterwards the fork[1]. This way
*	it's an asynchronous call of the forks and avoids deadlocks.
*	For example:
*		philo 0:
*			fork[0]= 0 (<left_fork>)
*			fork[1]= 1 (<right_fork>)
*		philo 1:
*			fork[0]= 1 (<right_fork>)
*			fork[1]= 0 (<left_fork>)
*/
void	init_forks(t_table *table, int i)
{
	if (table->philos[i]->id % 2 == 0)
	{
		table->philos[i]->fork[0]
			= table->philos[i]->id;
		table->philos[i]->fork[1]
			= (table->philos[i]->id + 1) % table->n_philos;
	}
	else
	{
		table->philos[i]->fork[0]
			= (table->philos[i]->id + 1) % table->n_philos;
		table->philos[i]->fork[1]
			= table->philos[i]->id;
	}
}

/* init_philos:
*	Allocates the memory for each Philosopher and initializes their
*	values (as far as known).
*	Return false in case of error (includes triggering error-message) and
*	true in case of success.
*/
bool	init_philos(t_table *table, char **argv)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		table->philos[i] = malloc(sizeof(t_philo));
		if (!table->philos[i])
			return (exit_philo(-1, table, STR_ERR_MALLOC, NULL), false);
		table->philos[i]->id = i;
		table->philos[i]->n_philos = table->n_philos;
		table->philos[i]->n_meals = 0;
		table->philos[i]->time_to_eat = (unsigned long long)atoi_uint(argv[3]);
		table->philos[i]->time_to_sleep
			= (unsigned long long)atoi_uint(argv[4]);
		table->philos[i]->gen_info = table->gen_info;
		table->philos[i]->mutexes = table->mutexes;
		init_forks(table, i);
		i++;
	}
	return (true);
}

/* init_mutexes:
*	Allocates memory and initializes the Mutexes of the struct t_mutex.
*	Return false in case of error (includes triggering error-message) and
*	true in case of success.
*/
bool	init_mutexes(t_table *table)
{
	int		i;

	table->mutexes->forks = malloc(sizeof(pthread_mutex_t) * table->n_philos);
	if (!table->mutexes->forks)
		return (exit_philo(-1, table, STR_ERR_MALLOC, NULL), false);
	i = 0;
	while (i < table->n_philos)
	{
		if (pthread_mutex_init(&table->mutexes->forks[i], 0))
			return (exit_philo(-1, table, STR_ERR_MUTEX, NULL), false);
		i++;
	}
	if (pthread_mutex_init(&table->mutexes->mutex_stop_sim, 0))
		return (exit_philo(-1, table, STR_ERR_MUTEX, NULL), false);
	if (pthread_mutex_init(&table->mutexes->mutex_time, 0))
		return (exit_philo(-1, table, STR_ERR_MUTEX, NULL), false);
	if (pthread_mutex_init(&table->mutexes->mutex_print, 0))
		return (exit_philo(-1, table, STR_ERR_MUTEX, NULL), false);
	return (true);
}

/* init_gen_info:
*	Initialize the data in t_gen_info and allocate the needed memory.
*	Return false in case of error (includes triggering error-message) and
*	true in case of success.
*/
bool	init_gen_info(t_table *table)
{
	table->gen_info->n_meals = malloc(sizeof(unsigned int) * table->n_philos);
	table->gen_info->t_last_meal = malloc(sizeof(unsigned long long)
			* table->n_philos);
	if (!table->gen_info->n_meals || !table->gen_info->t_last_meal)
		return (exit_philo(-1, table, STR_ERR_MALLOC, NULL), false);
	memset(table->gen_info->n_meals, 0,
		sizeof(unsigned int) * table->n_philos);
	memset(table->gen_info->t_last_meal, 0,
		sizeof(unsigned long long) * table->n_philos);
	table->gen_info->stop_sim = false;
	return (true);
}

/* init_observer:
*	Initializes all the values (except for t_start -> see init_simulation)
*	of the struct t_observer.
*	Return false in case of error (includes triggering error-message) and
*	true in case of success.
*/
bool	init_observer(t_table *table, int argc, char **argv)
{
	table->observer->n_philos = table->n_philos;
	if (argc == 6)
	{
		table->observer->n_min_meals = (int)atoi_uint(argv[5]);
		if (table->observer->n_min_meals == 0)
			return (exit_philo(-1, table, STR_SUC_0MEAL, NULL), false);
	}
	else
		table->observer->n_min_meals = -1;
	table->observer->time_to_die = (unsigned long long)atoi_uint(argv[2]);
	table->observer->mutexes = table->mutexes;
	table->observer->gen_info = table->gen_info;
	return (true);
}
