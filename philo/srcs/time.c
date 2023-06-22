/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:40:24 by fbecht            #+#    #+#             */
/*   Updated: 2023/06/16 13:40:30 by fbecht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* get_time_ms:
*	Returns the current time in ms.
*/
unsigned long long	get_time_ms(void)
{
    struct timeval	t;

    gettimeofday(&t, NULL);
	return ((unsigned long long)(t.tv_sec * 1000 + t.tv_usec / 1000));
}

/* set_start_time:
*	Initializes the start time (t_start) in each struct
*	with the current time in ms.
*/
void	set_start_time(t_table *table)
{
	int	i;

	table->t_start = get_time_ms();
	table->observer->t_start = table->t_start;
	i = -1;
	while (++i < table->n_philos)
	{
		table->philos[i]->t_start = table->t_start;
		//table->philos[i]->t_last_meal = table->t_start;
		table->gen_info->t_last_meal[i] = table->t_start;
	}
}
