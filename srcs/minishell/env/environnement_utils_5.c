/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement_utils_5.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:44:22 by jdenis            #+#    #+#             */
/*   Updated: 2024/01/22 18:40:44 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environnement.h"

char	*get_line(char *str)
{
	char	*tmp;

	tmp = ft_strdup(str);
	free(str);
	tmp[ft_strlen(tmp) - 1] = '\0';
	return (tmp);
}

char	**copy_environnement_from_file(int fd)
{
	size_t	index;
	size_t	length;
	char	**new;
	char	*str;

	length = size_of_new_env();
	index = 0;
	new = malloc(sizeof(char *) * (length + 1));
	if (!new)
		return (NULL);
	str = get_next_line(fd);
	while (str)
	{
		new[index] = get_line(str);
		if (!new[index])
		{
			free_strs(new);
			return (NULL);
		}
		str = get_next_line(fd);
		index++;
	}
	free(str);
	new[index] = NULL;
	return (new);
}

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
