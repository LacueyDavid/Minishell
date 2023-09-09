/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:25:38 by dlacuey           #+#    #+#             */
/*   Updated: 2023/05/12 18:25:41 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str_modified;
	size_t	index;

	index = 0;
	if (s == NULL)
		return (NULL);
	str_modified = ft_calloc(ft_strlen(s) + 1, 1);
	if (str_modified == NULL)
		return (NULL);
	while (s[index])
	{
		str_modified[index] = f(index, s[index]);
		index++;
	}
	return (str_modified);
}
