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

//#include "philo.h"
#include <stdio.h>
#include <sys/time.h>

unsigned long long	get_time_ms(void)
{
    struct timeval	t;

    gettimeofday(&t, NULL);
	return ((unsigned long long)(t.tv_sec * 1000 + t.tv_usec / 1000));
}
