/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:26:20 by dlacuey           #+#    #+#             */
/*   Updated: 2023/10/25 04:01:13 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*toobigstart(void)
{
	char	*str;

	str = malloc(1);
	if (str == NULL)
		return (NULL);
	str[0] = '\0';
	return (str);
}

static char	*str_fill(char const *s, unsigned int start, size_t len, char *str)
{
	size_t	index;
	size_t	size;

	index = 0;
	size = ft_strlen(s) - start + 1;
	if (len < size)
		str = malloc(len + 1);
	else
		str = malloc(ft_strlen(s) - start + 1);
	if (!str)
		return (NULL);
	while (s[start] && index < len)
	{
		str[index] = s[start];
		index++;
		start++;
	}
	str[index] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;

	str = NULL;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		str = toobigstart();
		return (str);
	}
	str = str_fill(s, start, len, str);
	return (str);
}
