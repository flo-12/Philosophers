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

/* free_table:
*	Frees all the data in table if it exists.
*	Precondition: table is not NULL
*/
void	free_table(t_table *table)
{
	unsigned int	i;

	if (table->philos)
	{
		i = -1;
		while (table->philos[++i])
			free(table->philos[i]);
		free(table->philos);
	}

	free(table);

	/* typedef struct s_table
	{
	unsigned long long	t_start;
	unsigned int		n_philos;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	unsigned int		n_min_meals;
	bool				died;
	t_philo				**philos;
	}	t_table; */
}

/* error_null:
*	Frees the data of table and prints out the message in str.
*/
void	error_free(char *str, char *arg1, char *arg2, t_table *table)
{
	if (table != NULL)
		free_table(table);
	msg(str, arg1, arg2);
}

