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
	if (!get_stop_sim(&philo->gen_info->stop_sim,
			&philo->mutexes->mutex_stop_sim))
		print_state(STR_STATE_FOR, philo->t_start, philo->id + 1,
			&philo->mutexes->mutex_print);
	pthread_mutex_lock(&philo->mutexes->forks[philo->fork[1]]);
	if (!get_stop_sim(&philo->gen_info->stop_sim,
			&philo->mutexes->mutex_stop_sim))
	{
		print_state(STR_STATE_FOR, philo->t_start, philo->id + 1,
			&philo->mutexes->mutex_print);
		print_state(STR_STATE_EAT, philo->t_start, philo->id + 1,
			&philo->mutexes->mutex_print);
	}
	pthread_mutex_lock(&philo->mutexes->mutex_meals[philo->id]);
	philo->gen_info->t_last_meal[philo->id] = get_time_ms();
	philo->t_last_meal = philo->gen_info->t_last_meal[philo->id];
	pthread_mutex_unlock(&philo->mutexes->mutex_meals[philo->id]);
	philo_wait(philo->time_to_eat, philo);
	pthread_mutex_unlock(&philo->mutexes->forks[philo->fork[1]]);
	pthread_mutex_unlock(&philo->mutexes->forks[philo->fork[0]]);
	pthread_mutex_lock(&philo->mutexes->mutex_meals[philo->id]);
	philo->gen_info->n_meals[philo->id]++;
	pthread_mutex_unlock(&philo->mutexes->mutex_meals[philo->id]);
}

/* sleep_routine:
*	Sleep routine prints out that the philosopher is sleeping
*	and waits the time a philosopher needs to sleep.
*/
void	sleep_routine(t_philo *philo)
{
	if (!get_stop_sim(&philo->gen_info->stop_sim,
			&philo->mutexes->mutex_stop_sim))
		print_state(STR_STATE_SLE, philo->t_start,
			philo->id + 1, &philo->mutexes->mutex_print);
	philo_wait(philo->time_to_sleep, philo);
}

/* think_routine:
*	Thinking routine prints out that the philosopher is thinking.
*/
void	think_routine(t_philo *philo)
{
	unsigned long long	t_think;

	if (!get_stop_sim(&philo->gen_info->stop_sim,
			&philo->mutexes->mutex_stop_sim))
		print_state(STR_STATE_THI, philo->t_start, philo->id + 1,
			&philo->mutexes->mutex_print);
	t_think = (philo->time_to_die - (get_time_ms() - philo->t_last_meal)) / 2;
	if (t_think < 100)
		t_think = 0;
	else if (t_think < 200)
		t_think = 100;
	else
		t_think = 200;
	philo_wait(t_think, philo);
}

/* single_philo_routine:
*	Routine if there is only one philosopher. In that case, the
*	philosopher graps the first (and only) fork and waits till
*	its's dead.
*/
void	single_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutexes->forks[philo->fork[0]]);
	print_state(STR_STATE_FOR, philo->t_start, philo->id + 1,
		&philo->mutexes->mutex_print);
	philo_wait(philo->time_to_die, philo);
	print_state(STR_STATE_DIE, philo->t_start, philo->id + 1,
		&philo->mutexes->mutex_print);
	pthread_mutex_unlock(&philo->mutexes->forks[philo->fork[0]]);
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
	if (philo->n_philos == 1)
	{
		single_philo_routine(philo);
		return (NULL);
	}
	time_sync(philo->t_start);
	if (philo->id % 2 == 1)
		think_routine(philo);
	while (!get_stop_sim(&philo->gen_info->stop_sim,
			&philo->mutexes->mutex_stop_sim))
	{
		eat_routine(philo);
		sleep_routine(philo);
		think_routine(philo);
	}
	return (NULL);
}
