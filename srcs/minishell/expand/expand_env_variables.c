/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:31:05 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/08 06:50:05 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "libft.h"
#include <stdbool.h>
#include <stdio.h>

static bool	expand_value(char **values, t_envs *envs)
{
	char	*value;
	char	*final_value;
	ssize_t	size_of_final_value;

	value = *values;
	size_of_final_value = count_final_value_size(value, envs);
	if (size_of_final_value == -1)
		return (false);
	final_value = malloc(size_of_final_value);
	if (!final_value)
		return (false);
	if (!fill_final_value(final_value, *values, envs))
		return (false);
	free(*values);
	*values = final_value;
	return (true);
}

bool	expand_env_variables(t_vector_strs *vector, t_envs *envs)
{
	int		index;
	char	**values;
	char	*value_after_expansion;

	values = vector->values;
	index = 0;
	if (values == NULL)
		return (true);
	while (values[index])
	{
		if (!expand_value(&(values[index]), envs))
			return (false);
		index++;
	}
	value_after_expansion = ft_strsjoin(values, " ");
	if (!value_after_expansion)
		return (false);
	free_strs(values);
	vector->values = ft_strtok(value_after_expansion, " ");
	if (!vector->values)
		return (false);
	vector->size = ft_strslen(vector->values);
	vector->capacity = vector->size;
	(remove_quotes(vector->values), free(value_after_expansion));
	return (true);
}
