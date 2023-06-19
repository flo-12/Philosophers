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

#include "philo.h"

/*
CHECK AGAIN:
	* in while loop in philosopher-fct: break if stop_sim is true
	* check mutexes in structs and think about which ones are necessary
		* mutex for time calculations in print_state
		* mutex to write state messages (avoid mixing up state messages)
		* necessary:
			- mutex_write_output (to print each state message)
			- mutex_forks (to lock each fork)
			- mutex_eat_enough (in table for each philo to mark if it ate enough)
			- mutex_n_eat (for the table_obs to check if a philo died of starvation)
	* break the eat/think/sleep routine if a philo dies of starvation
*/

void	print_table(t_table *table)
{
	unsigned int	i;

	printf("VALUES OF T_TABLE:\n");
	printf("n_philos=%u | time_to_die=%u | time_to_eat=%u | time_to_sleep=%u | n_min_meals=%u | died=%u\n", table->n_philos, table->time_to_die, table->time_to_eat, table->time_to_sleep, table->n_min_meals, table->died);
	
	i = 0;
	while (i < table->n_philos)
	{
		printf("Philo %u/%u: n_meals=%u | forks=[%u, %u]\n", i, table->philos[i]->id, table->philos[i]->n_meals, table->philos[i]->fork[0], table->philos[i]->fork[1]);
		if (table != (table->philos[i]->table))
			printf("Error address table\n");
		i++;
	}
}

/* init_simulation:
*	Initialize/Create all the threads for the simulation.
*	Return false in case of error and print error message and
*	otherwise true.
*/
bool	init_simulation(t_table *table)
{
	unsigned int	i;

	set_start_time(table);
	i = 0;
	while (i < table->n_philos)
	{
		if (pthread_create(&table->philos[i]->thread, NULL,
				&philosopher, table->philos[i]))
			return (error_free(STR_ERR_THREAD, NULL, NULL, table), false);
		i++;
	}
	// ... create meal_obs (to observe the state of the tables and stop the simulation)
	i = -1;
	while (++i < table->n_philos)
		pthread_join(table->philos[i]->thread, NULL);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	table = NULL;
	if (!is_valid_input(argc, argv))
		return (EXIT_FAILURE);
	table = init_table(argc, argv);
	if (!table)
		return (EXIT_FAILURE);
	//print_table(table);
	if (!init_simulation(table))
		return (EXIT_FAILURE);
	// stop simulation
	return (EXIT_SUCCESS);
}
