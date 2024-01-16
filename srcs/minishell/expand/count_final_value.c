/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_final_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:33:18 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/16 13:51:50 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "libft.h"

extern int		g_exit_status;

static bool	is_stop_expand_char(char c)
{
	char	i;

	i = 'A';
	while (i < 'z')
	{
		if (c == i)
			return (false);
		i++;
	}
	return (true);
}

static ssize_t	exit_status_size(void)
{
	char	*exit_status_str;
	size_t	index;

	exit_status_str = ft_itoa(g_exit_status);
	if (!exit_status_str)
		return (-1);
	index = ft_strlen(exit_status_str);
	free(exit_status_str);
	return (index);
}

static ssize_t dup_the_value_with_equal_at_end(char **dup_value, char *value, size_t *index2)
{
	*dup_value = ft_strdup(value);
	if (!dup_value)
		return (-1);
	while (!is_stop_expand_char(value[*index2]))
		(*index2)++;
	*dup_value[*index2] = '\0';
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

void	count_result_of_variable(size_t *index, size_t *index2,
			char *dup_value, t_envs *envs)
{
	while (envs->env[*index] && !ft_strnstr(envs->env[*index], dup_value,
			ft_strlen(envs->env[*index])))
		(*index)++;
	while (envs->env[*index][*index2] != '=')
		(*index2)++;
}

static ssize_t	count_actual_variable_size(char *value, t_envs *envs)
{
	size_t	index;
	size_t	index2;
	char	*dup_value;
	ssize_t return_value;

	index = 0;
	index2 = 0;
	//
	if (value[0] == '?')
		return (exit_status_size());
	//
	return_value = dup_the_value_with_equal_at_end(&dup_value, value, &index2);
	if (return_value)
		return (return_value);
	//
	count_result_of_variable(&index, &index2, dup_value, envs);
	while (envs->env[index] && !ft_strnstr(envs->env[index], dup_value,
										   ft_strlen(envs->env[index])))
		index++;
	free(dup_value);
	if (!envs->env[index])
		return (0);
	index2 = 0;
	while (envs->env[index][index2] != '=')
		index2++;
	dup_value = envs->env[index] + index2 + 1;
	//
	return (ft_strlen(dup_value));
}


static void	init_counter(t_counter *counter)
{
	counter->size = 0;
	counter->index = 0;
	counter->double_quote = false;
	counter->variable_size = 0;
}

ssize_t	count_variables(t_counter *counter, char *value, t_envs *envs)
{
	counter->index++;
	counter->variable_size
		= count_actual_variable_size(value + counter->index, envs);
	if (counter->variable_size == -1)
		return (-1);
	if (counter->variable_size == -2 && value[counter->index] == '\0')
	{
		counter->variable_size = 0;
		counter->size++;
	}
	else if (counter->variable_size == -2
			 && value[counter->index] != '\0')
		counter->variable_size = 0;
	if (counter->index > 1 && value[counter->index - 2] == '"'
		&& value[counter->index] == '"')
		counter->size++;
	counter->size += counter->variable_size;
	while (!is_stop_expand_char(value[counter->index]))
		counter->index++;
	if (value[counter->index] == '?')
		counter->index++;
	return (0);
}

static void	skip_single_quote(char *value, t_counter *counter)
{
	counter->index++;
	counter->size++;
	while (value[counter->index] != '\'')
	{
		counter->size++;
		counter->index++;
	}
	counter->index++;
	counter->size++;
}

ssize_t	count_final_value_size(char *value, t_envs *envs)
{
	t_counter	counter;

	init_counter(&counter);
	while (value[counter.index])
	{
		if (value[counter.index] == '$')
		{
			if (count_variables(&counter, value, envs) == -1)
				return (-1);
		}
		else if (value[counter.index] == '\'' && !counter.double_quote)
			skip_single_quote(value, &counter);
		else if (value[counter.index] == '"')
		{
			counter.double_quote = !counter.double_quote;
			counter.index++;
			counter.size++;
		}
		else
		{
			counter.size++;
			counter.index++;
		}
	}
	return (counter.size + 1);
}
