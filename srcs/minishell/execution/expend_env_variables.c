/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_env_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:31:05 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/06 09:40:36 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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

bool	expand_env_variables(char ***strs, t_envs *envs)
{
	int		i;
	char	**values = *strs;

	i = 0;
	while (values[i])
	{
		if(!expand_value(&(values[i]), envs))
			return false;
		i++;
	}
	return true;
}
