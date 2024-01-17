/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_final_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:33:18 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/17 13:32:19 by dlacuey          ###   ########.fr       */
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
	while (!is_stop_expand_char_to_count(value[counter->index]))
		counter->index++;
	if (value[counter->index] == '?')
		counter->index++;
	// printf("value 1/53 = %s\n", value);
	// printf("je sors de la fonction !\n");
	printf("counter->index 3 = %zu\n", counter->index);
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
			// printf("value %s\n", value);
			if (count_variables(&counter, value, envs) == -1)
				return (-1);
			printf("counter.index 2 = %zu\n", counter.index);
			// printf("je suis sortie de la fonction !\n");
			// printf("value 1/53 = %s\n", value);
			// printf("value 2 PUTAIN WTF = %p\n", value);
			// printf("value 2 = %s\n", value);
		}
		else if (value[counter.index] == '\'' && !counter.double_quote)
		{
			skip_single_quote(value, &counter);
		}
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
		printf("counter.index 1 = %zu\n", counter.index);
	}
	// printf("fin de %s\n", value);
	return (counter.size + 1);
}
