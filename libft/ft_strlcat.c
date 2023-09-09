/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:49:05 by dlacuey           #+#    #+#             */
/*   Updated: 2023/05/13 19:50:24 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	lendst;
	size_t	index;
	size_t	indexsrc;

	if (!dst && size == 0)
		return (ft_strlen(src));
	lendst = ft_strlen(dst);
	if (lendst >= size)
		return (size + ft_strlen(src));
	index = lendst;
	indexsrc = 0;
	while (index < size - 1 && src[indexsrc])
		dst[index++] = src[indexsrc++];
	dst[index] = '\0';
	return (lendst + ft_strlen(src));
}
