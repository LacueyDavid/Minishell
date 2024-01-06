/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_final_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:34:01 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/06 13:48:17 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "libft.h"

extern int exit_status;

#include <stdio.h>
static ssize_t	fill_actual_variable(char *final_value, char *value, t_envs *envs)
{
	size_t i = 0;
	size_t n = 0;
	char *exit_status_str;
	if (value[0] == '?')
	{
		exit_status_str = ft_itoa(exit_status);
		if (!exit_status_str)
			return -1;
		ft_strlcpy(final_value, exit_status_str, ft_strlen(exit_status_str) + 1);
		i = ft_strlen(exit_status_str);
		free(exit_status_str);
		return i;
	}
	char *dup_value = ft_strdup(value);
	if (!dup_value)
		return -1;
	while(value[n] != '"' && value[n] != '\'' && value[n] && value[n] != '$' && value[n] != '?')
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
	ft_strlcpy(final_value, dup_value, ft_strlen(dup_value) + 1);
	return ft_strlen(dup_value);
}

bool	fill_final_value(char *final_value, char *value, t_envs *envs)
{
	size_t i = 0;
	size_t j = 0;
	ssize_t variable_size;
	bool double_quote = false;

	while (value[i])
	{
		if (value[i] == '$')
		{
			i++;
			if (variable_size == -1)
				return false;
			variable_size = fill_actual_variable(final_value + j, value + i, envs);
			if (variable_size == -1)
				return false;
			j += variable_size;
			while(value[i] != '"' && value[i] != '\'' && value[i] && value[i] != '$' && value[i] != '?')
				i++;
			if (value[i] == '?')
				i++;
		}
		else if (value[i] == '\'' && !double_quote)
		{
			final_value[j] = value[i];
			j++;
			i++;
			while (value[i] != '\'')
			{
				final_value[j] = value[i];
				j++;
				i++;
			}
			final_value[j] = value[i];
			j++;
			i++;
		}
		else if (value[i] == '"')
		{
			double_quote = !double_quote;
			final_value[j] = value[i];
			j++;
			i++;
		}
		else
		{
			final_value[j] = value[i];
			j++;
			i++;
		}
	}
	final_value[j] = '\0';
	return true;
}

