/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 21:14:13 by jdenis            #+#    #+#             */
/*   Updated: 2024/01/15 21:15:02 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	print_empty_export(t_envs *envs)
{
	size_t	index;

	index = 0;
	while (envs->exports[index])
	{
		printf("declare -x %s\n", envs->exports[index]);
		index++;
	}
	return (EXIT_SUCCESS);
}

int	add_var_exp(char ***envs, char **input)
{
	size_t	index;
	size_t	index2;

	index = ft_strslen(*envs);
	*envs = realloc(*envs, sizeof(char *) * (ft_strslen(*envs)
				+ ft_strslen(input)));
	if (!*envs)
		return (EXIT_FAILURE);
	index2 = 1;
	while (input[index2])
	{
		(*envs)[index] = ft_strdup_with_quotes(input[index2]);
		if (!(*envs)[index])
		{
			free_strs(*envs);
			return (EXIT_FAILURE);
		}
		index++;
		index2++;
	}
	(*envs)[index] = NULL;
	return (EXIT_SUCCESS);
}

char	*ft_get_name(char *input)
{
	size_t	index;
	char	*name;

	index = 0;
	while (input[index] && input[index] != '=')
		index++;
	name = malloc(sizeof(char) * (index + 1));
	if (!name)
		return (NULL);
	index = 0;
	while (input[index] && input[index] != '=')
	{
		name[index] = input[index];
		index++;
	}
	name[index] = '\0';
	return (name);
}

int	add_var_env(char ***envs, char **input)
{
	size_t	index;
	size_t	index2;

	index = ft_strslen(*envs);
	*envs = realloc(*envs, sizeof(char *) * (ft_strslen(*envs)
				+ ft_strslen(input)));
	if (!*envs)
		return (EXIT_FAILURE);
	index2 = 1;
	while (input[index2])
	{
		if (ft_strchr(input[index2], '='))
		{
			(*envs)[index] = ft_strdup(input[index2]);
			if (!(*envs)[index])
			{
				free_strs(*envs);
				return (EXIT_FAILURE);
			}
			index++;
		}
		index2++;
	}
	(*envs)[index] = NULL;
	return (EXIT_SUCCESS);
}

bool	ft_is_in_env(char *name, char **envs)
{
	size_t	index;
	size_t	length;

	index = 0;
	length = ft_strlen(name);
	while (envs[index])
	{
		if (!ft_strncmp(envs[index], name, length))
			return (true);
		index++;
	}
	return (false);
}
