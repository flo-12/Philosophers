/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecht <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:49:03 by fbecht            #+#    #+#             */
/*   Updated: 2023/06/15 13:49:05 by fbecht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* contains_only_digits:
*	Check if string only contains digits.
*/
bool	contains_only_digits(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (false);
		str++;
	}
	return (true);
}

/* in_positive_range:
*	Check if str is bigger than max of an unsigned int (4,294,967,295).
*/
bool	in_positive_range(char *str, char *max_nbr)
{
	int	i;

	i = 0;
	if (ft_strlen(str) < ft_strlen(max_nbr))
		return (true);
	else if (ft_strlen(str) > ft_strlen(max_nbr))
		return (false);
	while (i < ft_strlen(max_nbr))
	{
		if (str[i] > max_nbr[i])
			return (false);
		else if (str[i] < max_nbr[i])
			break ;
		i++;
	}
	return (true);
}

/* is_valid_input:
*	Check if the user input is valid - with the following rules:
*		1) min of 4 and max of 5 strings
*		2) strings can only contain digits (also no spaces)
*		3) all strings (converted to a number) must be in the
*			range of an unsigned int
*	Return true if rules apply and otherwise false.
*/
bool	check_input(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (printf("%s", STR_ERR_USAGE), false);
	i = 0;
	while (argv[++i])
	{
		if (!contains_only_digits(argv[i]))
			return (printf(STR_ERR_INPUT_DIGIT, argv[i]), false);
		if (i == 1 && !in_positive_range(argv[i], STR_MAX_PHILOS))
			return (printf(STR_ERR_INPUT_MAXPHILOS, argv[i], STR_MAX_PHILOS), false);
		else if (i != 1 && !in_positive_range(argv[i], STR_MAX_U_INT))
			return (printf(STR_ERR_INPUT_DIGIT, argv[i]), false);
	}
	return (true);
}
