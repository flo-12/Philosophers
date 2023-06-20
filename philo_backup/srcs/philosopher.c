/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 10:32:14 by fbecht            #+#    #+#             */
/*   Updated: 2023/06/19 10:32:17 by fbecht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* eat_routine:
*	Eating routine lets a philosopher wait for both forks to
*	be available and graps the forks when they are available.
*	Also counts up the number of times the philosopher ate,
*	resets the starting time of the last meal and waits (usleep)
*	the time it takes to eat.
*/
void	eat_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->fork[0]]);
	print_state(STR_STATE_FOR, philo);
	pthread_mutex_lock(&philo->table->forks[philo->fork[1]]);
	print_state(STR_STATE_FOR, philo);
	print_state(STR_STATE_EAT, philo);
	philo->t_last_meal = get_time_ms();
	usleep(philo->table->time_to_eat);	// an extra function and mutex for that??
	pthread_mutex_unlock(&philo->table->forks[philo->fork[1]]);
	pthread_mutex_unlock(&philo->table->forks[philo->fork[0]]);
	philo->n_meals++;
}

/* sleep_routine:
*	Sleep routine waits (usleep) the time a philosopher needs
*	to sleep.
*/
void	sleep_routine(t_philo *philo)
{
	print_state(STR_STATE_SLE, philo);
	usleep(philo->table->time_to_sleep);
	/* extra sleep function has to be implemented:

	unsigned long long	wake_up;

	wake_up = get_time_ms() + time_to_sleep;
	while (get_time_ms() < wake_up)
	{
		if (get_stop_sim(philo->table))
			break ;	// or exit routine somehow???
		uslepp(1000);
	}
	*/
}

/* think_routine:
*	Thinking routine prints out that the philosopher is sleeping.
*	The philosopher will wait afterwards to grap the forks and
*	this time is "defined" (as the output in the Terminal) also
*	as thinking.
*/
void	think_routine(t_philo *philo)
{
	print_state(STR_STATE_THI, philo);
}

/* philosopher:
*	Routine for each Philosopher, which calls the function
*	to eat, think and sleep (in this order) and stops if
*	table->sim_stop is set to false.
*	Returns always NULL.
*/
void	*philosopher(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		sleep_routine(philo);
	while (1)
	{
		if (get_stop_sim(philo->table))
			break ;
		eat_routine(philo);
		if (get_stop_sim(philo->table))
			break ;
		sleep_routine(philo);
		if (get_stop_sim(philo->table))
			break ;
		think_routine(philo);
	}
	return (NULL);
}
