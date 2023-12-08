/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:06:05 by jdenis            #+#    #+#             */
/*   Updated: 2023/12/08 14:03:04 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environnement.h"
#include <stdlib.h>
#include "../../libft/libft.h"
#include <stdio.h>

extern char **environ;

void	free_envs(t_envs *envs)
{
	free_strs(envs->env);
	free_strs(envs->exports);
	free(envs);
}

char	**copy_environnement(char **env)
{
	size_t	index;
	size_t	length;

	length = 0;
	index = 0;
	while (environ[length])
		length++;
	env = malloc(sizeof(char *) * (length + 1));
	if (!env)
		return NULL;
	while (environ[index])
	{
		env[index] = ft_strdup(environ[index]);
		if (!env[index])
			return NULL;
		index++;
	}
	env[index] = NULL;
	return (env);
}

void	sort(char **exports)
{
	size_t	index;
	size_t	index2;
	char	*tmp;

	index = 0;
	index2 = 0;
	while (exports[index])
	{
		index2 = index + 1;
		while (exports[index2])
		{
			if (ft_strcmp(exports[index], exports[index2]) > 0)
			{
				tmp = exports[index];
				exports[index] = exports[index2];
				exports[index2] = tmp;
			}
			index2++;
		}
		index++;
	}
}

//pour pouvoir faire un export seul, difference : c'est dans l'ordre alphabetique et on ne prend pas les _=/usr/bin/env
char **copy_env_export(char **exports)
{
	size_t	index;
	size_t	index2;
	size_t	length;

	length = 0;
	index = 0;
	index2 = 0;
	while (environ[length])
		length++;
	exports = malloc(sizeof(char *) * (length));
	if (!exports)
		return NULL;
	while (environ[index])
	{
		if (!(environ[index][0] == '_' && environ[index][1] == '='))
		{
			exports[index2] = ft_strdup(environ[index]);
			if (!exports[index2])
				return NULL;
			index2++;
		}
		index++;
	}
	exports[index2] = NULL;
	sort(exports);
	return (exports);
}

t_envs	*copy_env_and_export(void)
{
	t_envs	*envs;

	envs = malloc(sizeof(t_envs));
	envs->env = copy_environnement(envs->env);
	envs->exports = copy_env_export(envs->exports);
	if (!envs->exports || !envs->env)
	{
		free_envs(envs);
		return (NULL);
	}
	return (envs);
}
