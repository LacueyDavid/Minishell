/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_final_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:33:18 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/06 10:39:01 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "libft.h"

static ssize_t count_actual_variable_size(char *value, t_envs *envs)
{
	size_t i = 0;
	// size_t size = 0;
	size_t n = 0;
	char *dup_value = ft_strdup(value);
	if (!dup_value)
		return -1;
	while(value[n] != '"' && value[n] != '\'' && value[n] && value[n] != '$')
		n++;
	dup_value[n] = '\0';
	if (!ft_add_char(&dup_value, '='))
		return -1;
	while(envs->env[i] && !ft_strnstr(envs->env[i], dup_value, ft_strlen(envs->env[i])))
		i++;
	free(dup_value);
	if (!envs->env[i])
		return 0;
	n = 0;
	while (envs->env[i][n] != '=')
		n++;
	dup_value = envs->env[i] + n + 1;
	return ft_strlen(dup_value);
}

ssize_t	count_final_value_size(char *value, t_envs *envs)
{
	size_t i = 0;
	size_t size = 0;
	ssize_t variable_size;
	bool double_quote = false;

	while (value[i])
	{
		if (value[i] == '$')
		{
			i++;
			variable_size = count_actual_variable_size(value + i, envs);
			if (variable_size == -1)
				return -1;
			size += variable_size;
			while(value[i] != '"' && value[i] != '\'' && value[i] && value[i] != '$')
				i++;
		}
		else if (value[i] == '\'' && !double_quote)
		{
			i++;
			size++;
			while (value[i] != '\'')
			{
				size++;
				i++;
			}
			i++;
			size++;
		}
		else if (value[i] == '"')
		{
			double_quote = !double_quote;
			i++;
			size++;
		}
		else
		{
			size++;
			i++;
		}
	}
	return size + 1;
}
