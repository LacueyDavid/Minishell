/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:49:21 by jdenis            #+#    #+#             */
/*   Updated: 2024/02/08 08:43:58 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	redo_export(char **input, size_t index, char ***env)
{
	size_t	index2;

	index2 = 1;
	while (input[index2])
	{
		if (input[index2][0] == '=' || !is_alpha_name(input[index2]))
		{
			printf("minishell: export: `%s': not a valid identifier\n",
				input[index2]);
			index2++;
			continue ;
		}
		(*env)[index] = ft_strdup_with_quotes(input[index2]);
		if (!(*env)[index])
		{
			free_strs(*env);
			*env = NULL;
			return (EXIT_FAILURE);
		}
		index++;
		index2++;
	}
	(*env)[index] = NULL;
	sort(*env);
	return (EXIT_SUCCESS);
}

int	redo_env(char **input, size_t index, char ***env)
{
	size_t	index2;

	index2 = 1;
	while (input[index2])
	{
		if (input[index2][0] == '=' || !is_alpha_name(input[index2]))
		{
			index2++;
			continue ;
		}
		if (ft_strchr(input[index2], '='))
		{
			(*env)[index] = ft_strdup(input[index2]);
			if (!(*env)[index])
			{
				free_strs(*env);
				*env = NULL;
				return (EXIT_FAILURE);
			}
			index++;
		}
		index2++;
	}
	(*env)[index] = NULL;
	return (EXIT_SUCCESS);
}
