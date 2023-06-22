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

#include "../includes/philo.h"

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
		if (get_stop_sim(&philo->gen_info->stop_sim, &philo->mutexes->mutex_stop_sim))
			break ;
		usleep(1000);
	}
}

/* eat_routine:
*	Eating routine lets a philosopher wait for both forks to
*	be available and graps the forks when they are available.
*	Also counts up the number of times the philosopher ate,
*	resets the starting time of the last meal and waits the
*	time it takes to eat.
*/
void	eat_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutexes->forks[philo->fork[0]]);
	if (!get_stop_sim(&philo->gen_info->stop_sim, &philo->mutexes->mutex_stop_sim))
		print_state(STR_STATE_FOR, philo->t_start, philo->id + 1, &philo->mutexes->mutex_print);
	pthread_mutex_lock(&philo->mutexes->forks[philo->fork[1]]);
	if (!get_stop_sim(&philo->gen_info->stop_sim, &philo->mutexes->mutex_stop_sim))
	{
		print_state(STR_STATE_FOR, philo->t_start, philo->id + 1, &philo->mutexes->mutex_print);
		print_state(STR_STATE_EAT, philo->t_start, philo->id + 1, &philo->mutexes->mutex_print);
	}
	pthread_mutex_lock(&philo->mutexes->mutex_stop_sim);
	//philo->t_last_meal = get_time_ms();
	philo->gen_info->t_last_meal[philo->id] = get_time_ms();
	pthread_mutex_unlock(&philo->mutexes->mutex_stop_sim);
	philo_wait(philo->time_to_eat, philo);
	pthread_mutex_unlock(&philo->mutexes->forks[philo->fork[1]]);
	pthread_mutex_unlock(&philo->mutexes->forks[philo->fork[0]]);
	pthread_mutex_lock(&philo->mutexes->mutex_stop_sim);
	//philo->n_meals++;
	philo->gen_info->n_meals[philo->id]++;
	pthread_mutex_unlock(&philo->mutexes->mutex_stop_sim);
}

/* sleep_routine:
*	Sleep routine prints out that the philosopher is sleeping
*	and waits the time a philosopher needs to sleep.
*/
void	sleep_routine(t_philo *philo)
{
	if (!get_stop_sim(&philo->gen_info->stop_sim, &philo->mutexes->mutex_stop_sim))
		print_state(STR_STATE_SLE, philo->t_start, philo->id + 1, &philo->mutexes->mutex_print);
	philo_wait(philo->time_to_sleep, philo);
}

/* think_routine:
*	Thinking routine prints out that the philosopher is thinking.
*/
void	think_routine(t_philo *philo)
{
	if (!get_stop_sim(&philo->gen_info->stop_sim, &philo->mutexes->mutex_stop_sim))
		print_state(STR_STATE_THI, philo->t_start, philo->id + 1, &philo->mutexes->mutex_print);
}

/* philosopher:
*	Routine for each Philosopher, which calls the function
*	to eat, think and sleep (in this order) and stops if
*	table->gen_info->stop_sim is set to false.
*	Returns always NULL.
*/
void	*philosopher(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		sleep_routine(philo);
	while (!get_stop_sim(&philo->gen_info->stop_sim, &philo->mutexes->mutex_stop_sim))
	{
		eat_routine(philo);
		sleep_routine(philo);
		think_routine(philo);
	}
	return (NULL);
}
