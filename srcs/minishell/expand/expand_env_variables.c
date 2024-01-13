/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:31:05 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/13 20:25:09 by dlacuey          ###   ########.fr       */
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

static void	remove_char(char *value)
{
	while (*value)
	{
		*value = *(value + 1);
		value++;
	}
}

static void	remove_untile_quote(char **value)
{
	remove_char(*value);
	while (**value && **value != '\'')
		(*value)++;
	remove_char(*value);
	(*value)--;
}

static void	remove_untile_double_quote(char **value)
{
	remove_char(*value);
	while (**value && **value != '\"')
		(*value)++;
	remove_char(*value);
	(*value)--;
}

void	remove_quotes_from_value(char *value)
{
	while (*value)
	{
		if (*value == '\'')
			remove_untile_quote(&value);
		if (*value == '\"')
			remove_untile_double_quote(&value);
		value++;
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
	free(value_after_expansion);
	return true;
}
