/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:48:50 by dlacuey           #+#    #+#             */
/*   Updated: 2023/05/12 18:48:54 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	index;
	char	*sdup;

	sdup = malloc(ft_strlen(s) + 1);
	if (!sdup)
		return (NULL);
	index = 0;
	while (s && s[index])
	{
		sdup[index] = s[index];
		index++;
	}
	sdup[index] = '\0';
	return (sdup);
}
