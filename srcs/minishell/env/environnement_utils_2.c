/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement_utils_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:44:22 by jdenis            #+#    #+#             */
/*   Updated: 2024/02/08 07:13:44 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environnement.h"

void	put_last_quotes(char *new, size_t index2, bool equal)
{
	if (equal)
	{
		new[index2] = '"';
		(index2)++;
	}
	new[index2] = '\0';
}

char	*ft_strdup_with_quotes(char *str)
{
	char	*new;
	size_t	index;
	size_t	index2;
	bool	equal;

	index = 0;
	index2 = 0;
	equal = false;
	new = malloc(ft_strlen(str) + 3);
	if (!new)
		return (NULL);
	while (str[index])
	{
		new[index2] = str[index];
		if (str[index] == '=' && !equal)
		{
			equal = true;
			++(index2);
			new[index2] = '"';
		}
		index++;
		index2++;
	}
	put_last_quotes(new, index2, equal);
	return (new);
}

size_t	copy_underscore_var_env(char **new, size_t index)
{
	new[index] = ft_strdup("_=/usr/bin/env");
	if (!new[index])
	{
		free_strs(new);
		exit(EXIT_FAILURE);
	}
	return (index + 1);
}
