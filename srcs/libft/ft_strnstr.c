/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:37:58 by dlacuey           #+#    #+#             */
/*   Updated: 2023/05/13 19:26:42 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	begin_of_little(const char *big, const char *little, size_t len)
{
	size_t	bigindex;

	bigindex = 0;
	while (*big && *little && *big == *little && bigindex < len)
	{
		big++;
		little++;
		bigindex++;
	}
	if (*little == '\0')
		return (1);
	return (0);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	index;

	index = 0;
	if (*little == '\0')
		return ((char *)big);
	while (index < len && *big && *little)
	{
		if (begin_of_little(big, little, len - index))
			return ((char *)big);
		index++;
		big++;
	}
	return (NULL);
}
