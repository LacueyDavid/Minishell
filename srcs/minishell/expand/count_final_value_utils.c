/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_final_value_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:10:10 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/08 07:46:30 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "libft.h"

extern int		g_exit_status;

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

static ssize_t	dup_the_value_with_equal_at_end(char **dup_value,
					char *value, size_t *index2)
{
	*dup_value = ft_strdup(value);
	if (!*dup_value)
		return (-1);
	while (value[*index2] && ft_isalnum(value[*index2]))
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

size_t	count_result_of_variable(size_t *index, size_t *index2,
			char **dup_value, t_envs *envs)
{
	if (!envs->env)
		return (0);
	while (envs->env[*index] && !ft_strbstr(envs->env[*index], *dup_value,
			ft_strlen(envs->env[*index])))
		(*index)++;
	free(*dup_value);
	if (!envs->env[*index])
		return (0);
	*index2 = 0;
	while (envs->env[*index][*index2] != '=')
		(*index2)++;
	*dup_value = envs->env[*index] + *index2 + 1;
	return (1);
}

ssize_t	count_actual_variable_size(char *value, t_envs *envs)
{
	size_t	index;
	size_t	index2;
	char	*dup_value;
	ssize_t	return_value;

	index = 0;
	index2 = 0;
	if (value[0] == '?')
		return (exit_status_size());
	return_value = dup_the_value_with_equal_at_end(&dup_value, value, &index2);
	if (return_value)
		return (return_value);
	if (!count_result_of_variable(&index, &index2, &dup_value, envs))
		return (0);
	return (ft_strlen(dup_value));
}
