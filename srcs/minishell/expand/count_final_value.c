/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_final_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:33:18 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/07 14:18:03 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "libft.h"

extern int	g_exit_status;

static void	init_counter(t_counter *counter)
{
	counter->size = 0;
	counter->index = 0;
	counter->double_quote = false;
	counter->variable_size = 0;
}

static ssize_t	count_variables(t_counter *counter, char *value, t_envs *envs)
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
	while (ft_isalnum(value[counter->index]))
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

static bool	check_validity_of_dollar(char *value, t_counter *counter,
				t_envs *envs)
{
	if (value[counter->index] == '$' && value[counter->index + 1] == '"')
	{
		counter->index += 1;
		counter->size += 1;
		return (true);
	}
	else if (value[counter->index] == '$'
		&& !ft_isalnum(value[counter->index + 1])
		&& value[counter->index + 1] != '?')
	{
		counter->index++;
		counter->size++;
		return (true);
	}
	if (value[counter->index] == '$')
	{
		if (count_variables(counter, value, envs) == -1)
			return (false);
	}
	return (true);
}

ssize_t	count_final_value_size(char *value, t_envs *envs)
{
	t_counter	counter;

	init_counter(&counter);
	while (value[counter.index])
	{
		if (!check_validity_of_dollar(value, &counter, envs))
			return (-1);
		else if (value[counter.index] && value[counter.index] == '\''
			&& !counter.double_quote)
			skip_single_quote(value, &counter);
		else if (value[counter.index] && value[counter.index] == '"')
		{
			counter.double_quote = !counter.double_quote;
			counter.index++;
			counter.size++;
		}
		else if (value[counter.index])
		{
			counter.size++;
			counter.index++;
		}
	}
	return (counter.size + 1);
}
