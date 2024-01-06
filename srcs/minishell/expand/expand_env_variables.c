/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:31:05 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/06 13:48:18 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "libft.h"
#include <stdio.h>
#include <stdbool.h>

static bool	expand_value(char **values, t_envs *envs)
{
	char *value = *values;
	char *final_value;
	ssize_t size_of_final_value;

	size_of_final_value = count_final_value_size(value, envs);
	if (size_of_final_value == -1)
		return false;
	final_value = malloc(size_of_final_value);
	if (!fill_final_value(final_value, *values, envs))
		return false;
	free(*values);
	*values = final_value;
	return true;
}

char *ft_strsjoin(char **strs, char *sep)
{
	char *result;
	int i = 0;
	int size = 0;
	int sep_size = ft_strlen(sep);

	while (strs[i])
	{
		size += ft_strlen(strs[i]);
		i++;
	}
	size += (i - 1) * sep_size;
	result = malloc(size + 1);
	result[0] = '\0';
	if (!result)
		return NULL;
	i = 0;
	while (strs[i])
	{
		ft_strlcat(result, strs[i], size + 1);
		if (strs[i + 1])
			ft_strlcat(result, sep, size + 1);
		i++;
	}
	return result;
}

void	remove_quotes_from_value(char *value)
{
	bool single_quotes = false;
	bool double_quotes = false;
	int index = 0;
	int index2 = 0;

	while (value[index])
	{
		index2 = index;
		if (value[index] == '\'' && !double_quotes)
		{
			single_quotes = !single_quotes;
			while (value[index2 + 1])
			{
				value[index2] = value[index2 + 1];
				index2++;
			}
			value[index2] = value[index2 + 1];
			index2++;
		}
		else if (value[index] == '"' && !single_quotes)
		{
			double_quotes = !double_quotes;
			while (value[index2 + 1])
			{
				value[index2] = value[index2 + 1];
				index2++;
			}
			value[index2] = value[index2 + 1];
			index2++;
		}
		index++;
	}
}

void	remove_quotes(char **values)
{
	int		index;

	index = 0;
	while (values[index])
	{
		remove_quotes_from_value(values[index]);
		index++;
	}
}

bool	expand_env_variables(t_vector_strs *vector, t_envs *envs)
{
	int		index;
	char	**values = vector->values;
	char	*value_after_expansion;

	index = 0;
	if(values == NULL)
		return true;
	while (values[index])
	{
		if(!expand_value(&(values[index]), envs))
			return false;
		index++;
	}
	value_after_expansion = ft_strsjoin(values, " ");
	if (!value_after_expansion)
		return false;
	free_strs(values);
	vector->values = ft_strtok(value_after_expansion, " ");
	vector->size = ft_strslen(vector->values);
	vector->capacity = vector->size;
	remove_quotes(vector->values);
	return true;
}
