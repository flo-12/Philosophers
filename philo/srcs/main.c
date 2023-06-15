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
		printf("Philo %u/%u: n_meals=%u | t_last_meal=%llu\n", i, table->philos[i]->id, table->philos[i]->n_meals, table->philos[i]->t_last_meal);
		if (table != (table->philos[i]->table))
			printf("Error address table\n");
		i++;
	}
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
	print_table(table);
	//if (!start)

	return (EXIT_SUCCESS);
}
