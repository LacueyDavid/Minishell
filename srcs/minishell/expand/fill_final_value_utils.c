/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_final_value_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:08:37 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/08 07:47:19 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "libft.h"
#include <stdio.h>

extern int	g_exit_status;

static ssize_t	fill_final_value_with_exit_status(char **final_value)
{
	char	*exit_status_str;
	size_t	index;

	if (g_exit_status == 4442)
		g_exit_status = 130;
	exit_status_str = ft_itoa(g_exit_status);
	if (!exit_status_str)
		return (-1);
	index = ft_strlen(exit_status_str);
	ft_strlcpy(*final_value, exit_status_str, ft_strlen(exit_status_str)
		+ 1);
	free(exit_status_str);
	return (index);
}

static ssize_t	dup_the_value_with_equal_at_end(char **dup_value,
					char *value, size_t *index2)
{
	*dup_value = ft_strdup(value);
	if (!*dup_value)
		return (-1);
	while (ft_isalnum(value[*index2]))
		(*index2)++;
	(*dup_value)[*index2] = '\0';
	if (*index2 == 0)
	{
		free(*dup_value);
		return (-2);
	}
	if (!ft_add_char(dup_value, '='))
	{
		free(*dup_value);
		return (-1);
	}
	return (0);
}

static bool	set_index_to_good_value(size_t *index, t_envs *envs,
					char *dup_value)
{
	if (!envs->env)
		return (false);
	while (envs->env[*index] && !ft_strbstr(envs->env[*index], dup_value,
			ft_strlen(envs->env[*index])))
		(*index)++;
	free(dup_value);
	if (!envs->env[*index])
		return (false);
	return (true);
}

static ssize_t	fill_actual_variable(char *final_value, char *value,
		t_envs *envs)
{
	size_t	index;
	size_t	index2;
	char	*dup_value;
	ssize_t	return_value;

	index = 0;
	index2 = 0;
	if (value[0] == '?')
		return (fill_final_value_with_exit_status(&final_value));
	return_value = dup_the_value_with_equal_at_end(&dup_value, value, &index2);
	if (return_value)
		return (return_value);
	if (!set_index_to_good_value(&index, envs, dup_value))
		return (0);
	index2 = 0;
	while (envs->env[index][index2] != '=')
		index2++;
	dup_value = envs->env[index] + index2 + 1;
	ft_strlcpy(final_value, dup_value, ft_strlen(dup_value) + 1);
	return (ft_strlen(dup_value));
}

bool	fill_variables(char *final_value, char *value, t_envs *envs,
			t_counter *counter)
{
	counter->variable_size = fill_actual_variable(final_value + counter->size,
			value + counter->index, envs);
	if (counter->variable_size == -1)
		return (false);
	if (counter->variable_size == -2 && value[counter->index] == '\0')
	{
		counter->variable_size = 0;
		final_value[counter->size] = '$';
		counter->size++;
	}
	else if (counter->variable_size == -2 && value[counter->index] != '\0')
		counter->variable_size = 0;
	if (counter->index > 1 && value[counter->index - 2] == '"'
		&& value[counter->index] == '"')
	{
		final_value[counter->size] = '$';
		counter->size++;
	}
	counter->size += counter->variable_size;
	while (ft_isalnum(value[counter->index]))
		counter->index++;
	if (value[counter->index] == '?')
		counter->index++;
	return (true);
}
