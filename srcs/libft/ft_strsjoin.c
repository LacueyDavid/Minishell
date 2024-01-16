/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 06:51:00 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/16 07:11:29 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_size_of_strs(char **strs, int sep_size)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (strs[i])
	{
		size += ft_strlen(strs[i]);
		i++;
	}
	size += (i - 1) * sep_size;
	return (size);
}

char	*ft_strsjoin(char **strs, char *sep)
{
	char	*result;
	int		i;
	int		size;
	int		sep_size;

	i = 0;
	size = 0;
	sep_size = ft_strlen(sep);
	size = count_size_of_strs(strs, sep_size);
	result = malloc(size + 1);
	if (!result)
		return (NULL);
	result[0] = '\0';
	i = 0;
	while (strs[i])
	{
		ft_strlcat(result, strs[i], size + 1);
		if (strs[i + 1])
			ft_strlcat(result, sep, size + 1);
		i++;
	}
	return (result);
}
