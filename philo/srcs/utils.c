/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:30:26 by fbecht            #+#    #+#             */
/*   Updated: 2023/06/15 16:30:28 by fbecht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* ft_strlen:
*	Get the length of a string.
*/
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
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
