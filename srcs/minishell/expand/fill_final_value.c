/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_final_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:34:01 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/07 14:20:11 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "libft.h"
#include <stdio.h>

extern int		g_exit_status;

static void	copy_single_quote(char *final_value, char *value,
				t_counter *counter)
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

static void	copy_double_quote(char *final_value, char *value,
				t_counter *counter)
{
	counter->double_quote = !counter->double_quote;
	final_value[counter->size] = value[counter->index];
	counter->size++;
	counter->index++;
}

static void	init_counter(t_counter *counter)
{
	counter->size = 0;
	counter->index = 0;
	counter->double_quote = false;
	counter->variable_size = 0;
}

static bool	check_validity_of_dollar(char *value, char *final_value,
				t_counter *counter, t_envs *envs)
{
	if (value[counter->index] == '$' && value[counter->index + 1] == '"')
	{
		final_value[counter->size] = value[counter->index];
		counter->index++;
		counter->size++;
		return (true);
	}
	else if (value[counter->index] == '$'
		&& !ft_isalnum(value[counter->index + 1])
		&& value[counter->index + 1] != '?')
	{
		final_value[counter->size] = value[counter->index];
		counter->size++;
		counter->index++;
		return (true);
	}
	if (value[counter->index] == '$')
	{
		counter->index++;
		if (counter->variable_size == -1)
			return (false);
		fill_variables(final_value, value, envs, counter);
	}
	return (true);
}

bool	fill_final_value(char *final_value, char *value, t_envs *envs)
{
	t_counter	counter;

	init_counter(&counter);
	while (value[counter.index])
	{
		if (!check_validity_of_dollar(value, final_value, &counter, envs))
			return (false);
		else if (value[counter.index] && value[counter.index] == '\''
			&& !counter.double_quote)
			copy_single_quote(final_value, value, &counter);
		else if (value[counter.index] && value[counter.index] == '"')
			copy_double_quote(final_value, value, &counter);
		else if (value[counter.index])
		{
			final_value[counter.size] = value[counter.index];
			counter.size++;
			counter.index++;
		}
	}
	final_value[counter.size] = '\0';
	return (true);
}
