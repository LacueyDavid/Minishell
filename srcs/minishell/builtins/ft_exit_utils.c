/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:39:37 by jdenis            #+#    #+#             */
/*   Updated: 2024/02/07 17:39:53 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

bool	bigger_nbr(char *nbr, char *max)
{
	size_t	index;

	index = 0;
	if (ft_strlen(nbr) > ft_strlen(max))
		return (1);
	if (ft_strlen(nbr) < ft_strlen(max))
		return (0);
	while (nbr[index] && max[index])
	{
		if (nbr[index] > max[index])
			return (1);
		index++;
	}
	return (0);
}

bool	smaller_nbr(char *nbr, char *min)
{
	size_t	index;

	index = 0;
	nbr++;
	min++;
	if (ft_strlen(nbr) > ft_strlen(min))
		return (1);
	if (ft_strlen(nbr) < ft_strlen(min))
		return (0);
	while (nbr[index] && min[index])
	{
		if (nbr[index] > min[index])
			return (1);
		index++;
	}
	return (0);
}

bool	between_max_min(char *nbr)
{
	if (nbr[0] == '-')
		return (smaller_nbr(nbr, "-9223372036854775808"));
	return (bigger_nbr(nbr, "9223372036854775807"));
}
