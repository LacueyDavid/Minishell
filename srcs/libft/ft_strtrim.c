/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:32:54 by dlacuey           #+#    #+#             */
/*   Updated: 2023/05/12 18:33:21 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char const c, char const *set)
{
	size_t	check;

	check = 0;
	while (*set)
	{
		if (c == *set)
			check = 1;
		set++;
	}
	return (check);
}

static size_t	how_much_skip(char const *s1, char const *set, size_t index)
{
	size_t	count;

	count = 0;
	if (index > 0)
		while (index > 0 && is_in_set(s1[index--], set))
			count++;
	else
		while (s1[count] && is_in_set(s1[count], set))
			count++;
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	memtocut;
	size_t	l;
	size_t	r;
	char	*str;

	l = 0;
	r = 0;
	memtocut = 0;
	str = NULL;
	if (s1 == NULL || set == NULL)
		return (NULL);
	l = how_much_skip(s1, set, 0);
	r = how_much_skip(s1, set, ft_strlen(s1) - 1);
	memtocut = l + r;
	str = ft_substr(s1, l, ft_strlen(s1) - memtocut);
	if (str == NULL)
		return (NULL);
	return (str);
}
