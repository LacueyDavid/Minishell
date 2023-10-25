/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:18:32 by dlacuey           #+#    #+#             */
/*   Updated: 2023/10/25 03:59:26 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	size_t	index;
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = malloc(size);
	index = 0;
	if (str == NULL)
		return (NULL);
	while (index < ft_strlen(s1))
	{
		str[index] = s1[index];
		index++;
	}
	str[index] = '\0';
	ft_strlcat(str, s2, size);
	return (str);
}
