/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 21:15:11 by dlacuey           #+#    #+#             */
/*   Updated: 2023/10/25 01:29:30 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	ft_size_min(size_t a, size_t b)
{
	if (a < b)
		return (a);
	return (b);
}

void	*ft_realloc(void *ptr, size_t new_size, size_t old_size)
{
	void *new_ptr;

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (ptr)
	{
		ft_memcpy(new_ptr, ptr, ft_size_min(new_size, old_size));
		free(ptr);
	}
	return (new_ptr);
}

