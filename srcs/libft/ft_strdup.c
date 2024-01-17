/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:48:50 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/17 13:14:30 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	index;
	char	*strdup;

	if (!str)
		return (NULL);
	strdup = malloc(ft_strlen(str) + 1);
	if (!strdup)
		return (NULL);
	index = 0;
	while (str[index])
	{
		strdup[index] = str[index];
		index++;
	}
	strdup[index] = '\0';
	return (strdup);
}
