/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_final_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:34:01 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/16 14:01:12 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "libft.h"
#include <stdio.h>

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

static ssize_t	fill_actual_variable(char *final_value, char *value,
		t_envs *envs)
{
	size_t	i;
	size_t	n;
	char	*exit_status_str;
	char	*dup_value;

	i = 0;
	n = 0;
	if (value[0] == '?')
	{
		exit_status_str = ft_itoa(g_exit_status);
		if (!exit_status_str)
			return (-1);
		ft_strlcpy(final_value, exit_status_str, ft_strlen(exit_status_str)
			+ 1);
		i = ft_strlen(exit_status_str);
		free(exit_status_str);
		return (i);
	}
	dup_value = ft_strdup(value);
	if (!dup_value)
		return (-1);
	while (!is_stop_expand_char(value[n]))
		n++;
	dup_value[n] = '\0';
	if (n == 0)
	{
		free(dup_value);
		return (-2);
	}
	if (!ft_add_char(&dup_value, '='))
	{
		free(dup_value);
		return (-1);
	}
	while (envs->env[i] && !ft_strnstr(envs->env[i], dup_value,
			ft_strlen(envs->env[i])))
		i++;
	free(dup_value);
	if (!envs->env[i])
		return (0);
	n = 0;
	while (envs->env[i][n] != '=')
		n++;
	dup_value = envs->env[i] + n + 1;
	ft_strlcpy(final_value, dup_value, ft_strlen(dup_value) + 1);
	return (ft_strlen(dup_value));
}

static void	init_counter(t_counter *counter)
{
	counter->size = 0;
	counter->index = 0;
	counter->double_quote = false;
	counter->variable_size = 0;
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
	if (counter->index > 1 && value[counter->index - 2] == '"' &&
			value[counter->index] == '"')
	{
		final_value[counter->size] = '$';
		counter->size++;
	}
	counter->size += counter->variable_size;
	while (!is_stop_expand_char(value[counter->index]))
		counter->index++;
	if (value[counter->index] == '?')
		counter->index++;
	return (true);
}

void	copy_single_quote(char *final_value, char *value, t_counter *counter)
{
	final_value[counter->size] = value[counter->index];
	counter->size++;
	counter->index++;
	while (value[counter->index] != '\'')
	{
		final_value[counter->size] = value[counter->index];
		counter->size++;
		counter->index++;
	}
	final_value[counter->size] = value[counter->index];
	counter->size++;
	counter->index++;
}

void	copy_double_quote(char *final_value, char *value, t_counter *counter)
{
	counter->double_quote = !counter->double_quote;
	final_value[counter->size] = value[counter->index];
	counter->size++;
	counter->index++;
}

bool	fill_final_value(char *final_value, char *value, t_envs *envs)
{
	t_counter	counter;

	init_counter(&counter);
	while (value[counter.index])
	{
		if (value[counter.index] == '$')
		{
			counter.index++;
			if (counter.variable_size == -1)
				return (false);
			fill_variables(final_value, value, envs, &counter);
		}
		else if (value[counter.index] == '\'' && !counter.double_quote)
			copy_single_quote(final_value, value, &counter);
		else if (value[counter.index] == '"')
			copy_double_quote(final_value, value, &counter);
		else
		{
			final_value[counter.size] = value[counter.index];
			counter.size++;
			counter.index++;
		}
	}
	final_value[counter.size] = '\0';
	return (true);
}
