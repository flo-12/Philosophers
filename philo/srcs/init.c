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

#include "philo.h"

/* assign_forks:
*	Assigns the index of two forks to the Philosopher. The index refers to
*	the forks the Philosopher picks up to eat - and their order.
*	Even-numbered Philosophers first pick up the left fork and then the
*	right fork and uneven-numbered Philosophers vice-versa.
*	This order is important to not get a deadlock in case that all Philosophers
*	want to eat at the same time, pick up first the left fork and can't pick
*	up the right fork because it's taken by the Philosopher to their right.
*	This method guarantees abn asynchronic lock of the forks and avoids
*	deadlocks.
*/
void	assign_forks(t_philo *philo, unsigned int n_philos)
{
	if (philo->id % 2 == 0)
	{
		philo->fork[0] = philo->id;
		philo->fork[1] = (philo->id + 1) % n_philos;
	}
	else
	{
		philo->fork[0] = (philo->id + 1) % n_philos;;
		philo->fork[1] = philo->id;
	}	
}

/* init_philos:
*	Allocates the memory for each Philosopher and initializes
*	their values (as far as known).
*	Returns a pointer to the array of pointers to the t_philo
*	for each Philosopher or NULL in case of failure.
*/
t_philo	**init_philos(t_table *table)
{
	t_philo			**philos;
	unsigned int	i;

	philos = malloc(sizeof(t_philo *) * table->n_philos);
	if (!philos)
		return (error_free(STR_ERR_MALLOC, NULL, NULL, table), NULL);
	i = 0;
	while (i < table->n_philos)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
			return (error_free(STR_ERR_MALLOC, NULL, NULL, table), NULL);
		philos[i]->id = i;
		philos[i]->n_meals = 0;
		philos[i]->table = table;
		assign_forks(philos[i], table->n_philos);
		i++;
	}
	return (philos);
}

/* atoi_uint:
*	Converts a string into an unsigned int.
*	Return the unsigned int.
*	Precondition: str is in the range of an unsigned int
*		and only consists digits.
*/
unsigned int	atoi_uint(char *str)
{
	int				i;
	unsigned int	nbr;

	nbr = 0;
	i = -1;
	while (str[++i])
		nbr = nbr * 10 + (str[i] - '0');
	return (nbr);
}

/* init_mutex_table:
*	Allocates memory and initializes the Mutexes of the struct t_table.
*	Return false in case of error and true in case of success.
*/
bool	init_mutex_table(t_table *table)
{
	unsigned int		i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->n_philos);
	if (!table->forks)
		return (false);
	i = 0;
	while (i < table->n_philos)
	{
		if (pthread_mutex_init(&table->forks[i], 0))
			return (false);
		i++;
	}
	if (pthread_mutex_init(&table->mutex_stop_sim, 0))
		return (false);
	if (pthread_mutex_init(&table->mutex_time, 0))
		return (false);
	return (true);
}

/* init_table:
*	Initialize the table struct with the user input containing
*	the program's parameters and initializing the other
*	variables.
*	Returns a pointer to the table structure or NULL in case
*	an error occured.
*
*/
t_table	*init_table(int argc, char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table) * 1);
	if (!table)
		return (error_free(STR_ERR_MALLOC, NULL, NULL, NULL), NULL);
	table->n_philos = atoi_uint(argv[1]);
	table->time_to_die = atoi_uint(argv[2]);
	table->time_to_eat = atoi_uint(argv[3]);
	table->time_to_sleep = atoi_uint(argv[4]);
	if (argc == 6)
	{
		table->n_min_meals = atoi_uint(argv[5]);
		if (table->n_min_meals == 0)
			return (error_free(STR_SUC_0MEAL, NULL, NULL), NULL);
	}
	else
		table->n_min_meals = 0;
	if (!init_mutex_table(table))
		return (error_free(STR_ERR_MUTEX, NULL, NULL, table), NULL);
	table->philos = init_philos(table);
	if (!table->philos)
		return (NULL);
	table->died = false;
	return (table);
}
