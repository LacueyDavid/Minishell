/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strs_to_ints.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:02:55 by dlacuey           #+#    #+#             */
/*   Updated: 2023/08/02 09:33:24 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strs_to_ints(int *array, char **argv)
{
	size_t	index;
	size_t	index2;

	index = 0;
	index2 = 1;
	while (argv[index])
	{
		array[index2] = ft_atoi(argv[index]);
		index++;
		index2++;
	}
}
