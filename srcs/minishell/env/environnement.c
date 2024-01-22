/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:06:05 by jdenis            #+#    #+#             */
/*   Updated: 2024/01/22 15:27:06 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environnement.h"
#include "builtins.h"

extern char	**environ;

size_t	copy_shlvl_var(char *shlvl_var, char **new, size_t index)
{
	char	*tmp;

	tmp = increased_shlvl(shlvl_var);
	new[index] = ft_strdup_with_quotes(tmp);
	free(tmp);
	if (!new[index])
	{
		free_strs(new);
		exit(EXIT_FAILURE);
	}
	return (index + 1);
}

size_t	copy_other_var(char *other_var, char **new, size_t index)
{
	new[index] = ft_strdup_with_quotes(other_var);
	if (!new[index])
	{
		free_strs(new);
		exit(EXIT_FAILURE);
	}
	return (index + 1);
}

char	**copy_env_export(void)
{
	size_t	index;
	size_t	index2;
	char	**new;

	new = malloc(sizeof(char *) * ft_strslen(environ));
	if (!new)
		return (NULL);
	index = 0;
	index2 = 0;
	while (environ[index])
	{
		if (ft_strncmp(environ[index], "SHLVL=", 6) == 0)
			index2 = copy_shlvl_var(environ[index], new, index2);
		else if (!(environ[index][0] == '_' && environ[index][1] == '='))
			index2 = copy_other_var(environ[index], new, index2);
		index++;
	}
	new[index2] = NULL;
	sort(new);
	return (new);
}

// char	**copy_env_export(void)
// {
// 	size_t	index;
// 	size_t	index2;
// 	size_t	length;
// 	char	**new;
// 	char	*tmp;

// 	length = 0;
// 	index = 0;
// 	index2 = 0;
// 	while (environ[length])
// 		length++;
// 	new = malloc(sizeof(char *) * (length));
// 	if (!new)
// 		return (NULL);
// 	while (environ[index])
// 	{
// 		if (ft_strncmp(environ[index], "SHLVL=", 6) == 0)
// 		{
// 			tmp = increased_shlvl(environ[index]);
// 			new[index2] = ft_strdup_with_quotes(tmp);
// 			free(tmp);
// 			if (!new[index2])
// 			{
// 				free_strs(new);
// 				return (NULL);
// 			}
// 			index2++;
// 		}
// 		else if (!(environ[index][0] == '_' && environ[index][1] == '='))
// 		{
// 			new[index2] = ft_strdup_with_quotes(environ[index]);
// 			if (!new[index2])
// 			{
// 				free_strs(new);
// 				return (NULL);
// 			}
// 			index2++;
// 		}
// 		index++;
// 	}
// 	new[index2] = NULL;
// 	sort(new);
// 	return (new);
// }

t_envs	*copy_env_and_export(void)
{
	t_envs	*envs;

	envs = malloc(sizeof(t_envs));
	if (!envs)
		return (NULL);
	envs->env = copy_environnement();
	envs->exports = copy_env_export();
	if (!envs->exports || !envs->env)
	{
		free_envs(envs);
		return (NULL);
	}
	return (envs);
}
