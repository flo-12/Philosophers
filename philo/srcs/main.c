/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:46:08 by fbecht            #+#    #+#             */
/*   Updated: 2023/06/13 12:46:09 by fbecht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* init_table:
*	Initialize the table struct with the user input containing
*	the program's parameters and initializing the other
*	variables.
*	Returns a pointer to the table structure or NULL in case
*	an error occured.
*/
t_table	*init_table(int argc, char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (exit_philo(-1, table, STR_ERR_MALLOC, NULL), NULL);
	table->n_philos = (int)atoi_uint(argv[1]);
	table->observer = malloc(sizeof(t_observer) * 1);
	table->mutexes = malloc(sizeof(t_mutex) * 1);
	table->philos = malloc(sizeof(t_philo *) * table->n_philos);
	table->gen_info = malloc(sizeof(t_gen_info) * 1);
	if (!table->observer || !table->mutexes || !table->philos
		|| !table->gen_info)
		return (exit_philo(-1, table, STR_ERR_MALLOC, NULL), NULL);
	if (!init_gen_info(table))
		return (NULL);
	if (!init_mutexes(table))
		return (NULL);
	if (!init_observer(table, argc, argv))
		return (NULL);
	if (!init_philos(table, argv))
		return (NULL);
	return (table);
}

/* init_simulation:
*	Initialize/Create all the threads for the simulation and 
*	call pthread_join for each thread.
*	Return false in case of error (includes triggering error-
*	message) and
*	true in case of success.
*/
bool	init_simulation(t_table *table)
{
	int	i;

	set_start_time(table);
	i = -1;
	while (++i < table->n_philos)
	{
		if (pthread_create(&table->philos[i]->thread, NULL,
				philosopher, table->philos[i]))
			return (exit_philo(i, table, STR_ERR_THREAD, NULL), false);
	}
	if (table->n_philos > 1)
	{
		if (pthread_create(&table->observer->thread, NULL,
				observer, table->observer))
			return (exit_philo(table->n_philos, table, STR_ERR_THREAD, NULL),
				false);
	}
	i = -1;
	while (++i < table->n_philos)
		pthread_join(table->philos[i]->thread, NULL);
	if (table->n_philos > 1)
		pthread_join(table->observer->thread, NULL);
	return (true);
}

/* main:
*	Calls all the functions and at the end terminates the
*	program.
*/
int	main(int argc, char **argv)
{
	t_table	*table;
// CHECK FOR MEM-LEAKS WITH VALGRIND
	table = NULL;
	if (!check_input(argc, argv))
		return (EXIT_FAILURE);
	table = init_table(argc, argv);
	if (!table)
		return (EXIT_FAILURE);
	if (!init_simulation(table))
		return (EXIT_FAILURE);
	exit_philo(-1, table, NULL, NULL);
	return (EXIT_SUCCESS);
}
