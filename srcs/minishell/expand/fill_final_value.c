/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_final_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:34:01 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/17 15:26:35 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "libft.h"
#include <stdio.h>

extern int		g_exit_status;

bool	is_stop_expand_char(char c)
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
