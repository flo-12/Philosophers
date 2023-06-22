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


void	print_table(t_table *table)
{
	int	i;

	printf("VALUES OF T_TABLE:\n");
	printf("n_philos=%d\n", table->n_philos);
	
	i = 0;
	while (i < table->n_philos)
	{
		if (i == 0 || i + 1 == table->n_philos)
			printf("PHILO VALUES: id=%u | n_meals=%u | time_to_eat=%llu | time_to_sleep=%llu | forks=[%d, %d]\n", table->philos[i]->id, table->philos[i]->n_meals, table->philos[i]->time_to_eat, table->philos[i]->time_to_sleep, table->philos[i]->fork[0], table->philos[i]->fork[1]);
		if (table->philos[i]->gen_info != table->gen_info)
			printf("Error address gen_info\n");
		if (table->philos[i]->mutexes != table->mutexes)
			printf("Error address mutexes\n");
		i++;
	}
	printf("OBSERVER VALUES: n_philos=%d | n_min_meals=%d | time_to_die=%llu\n", table->observer->n_philos, table->observer->n_min_meals, table->observer->time_to_die);
	if (table->observer->gen_info != table->gen_info)
		printf("Error address gen_info\n");
	if (table->observer->mutexes != table->mutexes)
		printf("Error address mutexes\n");
	printf("GEN_INFO VALUES: stop_sim=%d\n", table->gen_info->stop_sim);
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
	if (pthread_create(&table->observer->thread, NULL, observer, table->observer))
		return (exit_philo(table->n_philos, table, STR_ERR_THREAD, NULL), false);
	i = -1;
	while (++i < table->n_philos)
		pthread_join(table->philos[i]->thread, NULL);
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

	table = NULL;
	if (!check_input(argc, argv))
		return (EXIT_FAILURE);
	table = init_table(argc, argv);
	if (!table)
		return (EXIT_FAILURE);
	//print_table(table);
	if (!init_simulation(table))
		return (EXIT_FAILURE);
	//exit_philo(table->n_philos, table, NULL, NULL);
	exit_philo(-1, table, NULL, NULL);
	return (EXIT_SUCCESS);
}
