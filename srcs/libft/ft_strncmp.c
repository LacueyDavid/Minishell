/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:49:40 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/08 07:31:46 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	index;

	index = 0;
	if (n == 0)
		return (0);
	while (*s1 && *s2 && index < n - 1 && *s1 == *s2)
	{
		s1++;
		s2++;
		index++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
