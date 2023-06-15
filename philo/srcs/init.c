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
		table->n_min_meals = atoi_uint(argv[5]);
	table->philos = init_philos(table);
	if (!table->philos)
		return (NULL);
	table->died = false;
	return (table);
}
