/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:34:49 by jdenis            #+#    #+#             */
/*   Updated: 2024/02/07 17:13:53 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	skip_space(const char *nptr)
{
	int	index;

	index = 0;
	while ((nptr[index] >= '\t' && nptr[index] <= '\r') || nptr[index] == ' ')
		index++;
	return (index);
}

static int	get_sign(const char *nptr, int index)
{
	if (nptr[index] == '-')
		return (-1);
	else if (nptr[index] == '+')
		return (1);
	return (0);
}

long	ft_atol(const char *nptr)
{
	long	number;
	int		index;
	int		sign;

	number = 0;
	index = skip_space(nptr);
	sign = get_sign(nptr, index);
	if (sign)
		index++;
	else
		sign = 1;
	while (nptr[index])
	{
		if (nptr[index] < '0' || nptr[index] > '9')
			return (number * sign);
		number = number * 10 + nptr[index] - '0';
		index++;
	}
	return (number * sign);
}
