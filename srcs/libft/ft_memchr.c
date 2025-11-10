/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:32:01 by dlacuey           #+#    #+#             */
/*   Updated: 2023/05/13 19:47:09 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*sbis;

	i = 0;
	sbis = (unsigned char *)s;
	while (i < n)
	{
		if (sbis[i] == (unsigned char)c)
			return (&(sbis[i]));
		i++;
	}
	return (NULL);
}
