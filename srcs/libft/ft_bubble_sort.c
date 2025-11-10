/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bubble_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:03:22 by dlacuey           #+#    #+#             */
/*   Updated: 2023/07/25 16:03:35 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bubble_sort(int *array, size_t size)
{
	size_t	index;

	index = 0;
	while (index < size - 1)
	{
		if (array[index] > array[index + 1])
		{
			ft_swap(&array[index], &array[index + 1]);
			index = 0;
		}
		else
			index++;
	}
}
