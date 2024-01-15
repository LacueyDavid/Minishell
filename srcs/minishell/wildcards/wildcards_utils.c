/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 20:36:40 by jdenis            #+#    #+#             */
/*   Updated: 2024/01/15 20:39:45 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"

char	*ft_strchr_with_quote(const char *s, int c)
{
	bool	single_quote;
	bool	double_quote;

	single_quote = false;
	double_quote = false;
	while (*s)
	{
		if (*s == '\'')
			single_quote = !single_quote;
		if (*s == '\"')
			double_quote = !double_quote;
		if (*s == (char)c && !single_quote && !double_quote)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

int	match_end(char *file)
{
	size_t	index;

	index = 0;
	while (file[index] == '*')
		index++;
	if (file[index] == '\0' || file[index] == '*')
		return (1);
	return (0);
}

int	wildcard_match(const char *dir_file, char *wildcarded_file)
{
	while (*dir_file && *wildcarded_file)
	{
		if (*wildcarded_file == '*')
		{
			while (*wildcarded_file == '*')
				wildcarded_file++;
			if (*wildcarded_file == '\0')
				return (1);
			while (*dir_file)
			{
				if (wildcard_match(dir_file, wildcarded_file))
					return (1);
				dir_file++;
			}
			return (0);
		}
		if (*dir_file != *wildcarded_file)
			return (0);
		dir_file++;
		wildcarded_file++;
	}
	if (*dir_file == '\0' && match_end(wildcarded_file))
		return (1);
	return (0);
}

void	add_file(char ***values, char *file)
{
	size_t	index;
	size_t	index2;
	char	**new_values;

	index = 0;
	index2 = 0;
	while ((*values)[index])
		index++;
	new_values = (char **)malloc(sizeof(char *) * (index + 2));
	while (index2 < index)
	{
		new_values[index2] = ft_strdup((*values)[index2]);
		index2++;
	}
	new_values[index] = ft_strdup(file);
	new_values[index + 1] = NULL;
	free_strs(*values);
	*values = new_values;
}

size_t	count_files(char **values, char *file)
{
	size_t	index;
	size_t	index2;

	index = 0;
	index2 = 0;
	while (values[index])
	{
		if (strcmp(values[index], file) != 0)
			index2++;
		index++;
	}
	return (index2);
}
