/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:46:36 by dlacuey           #+#    #+#             */
/*   Updated: 2023/05/13 02:09:54 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*str;
	size_t	index;

	str = NULL;
	index = 0;
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (((nmemb * size) / size) != nmemb)
		return (NULL);
	str = malloc(nmemb * size);
	if (str == NULL)
		return (NULL);
	while (index < nmemb * size)
	{
		str[index] = 0;
		index++;
	}
	return (str);
}
