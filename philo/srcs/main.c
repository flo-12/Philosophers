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

/* simulation:
*	
*/
bool	simulation(t_table *table)
{
	unsigned int	i;

	table->t_start = get_time_ms();
	i = 0;
	while (i < table->n_philos)
	{
		if (pthread_create(&table->philos[i]->thread, NULL,
				&philosopher, table->philos[i]))
			return (error_free(STR_ERR_THREAD, NULL, NULL, table), false);
		i++;
	}
	// ...
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
	if (!simulation(table))
		return (EXIT_FAILURE);
	// stop simulation
	return (EXIT_SUCCESS);
}
