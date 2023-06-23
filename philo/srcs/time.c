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
		table->gen_info->t_last_meal[i] = table->t_start;
	}
}

/* philo_wait:
*	Lets the philosopher slepp for a given amount of time, but
*	checks every 1 ms if the simulation is finished (a philosopher
*	died or all meals are reached) and breaks if this happens.
*/
void	philo_wait(unsigned long long time_to_sleep, t_philo *philo)
{
	unsigned long long	wake_up;

	wake_up = get_time_ms() + time_to_sleep;
	while (get_time_ms() < wake_up)
	{
		if (get_stop_sim(&philo->gen_info->stop_sim,
				&philo->mutexes->mutex_stop_sim))
			break ;
		usleep(1000);
	}
}
