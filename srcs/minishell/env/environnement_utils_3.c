/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement_utils_3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:47:03 by jdenis            #+#    #+#             */
/*   Updated: 2024/02/08 07:12:24 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environnement.h"
#include "builtins.h"

extern char	**environ;

void	free_envs(t_envs *envs)
{
	if (!envs)
		return ;
	free_strs(envs->env);
	free_strs(envs->exports);
	free(envs);
}

size_t	copy_shlvl_var_env(char *shlvl_var, char **new, size_t index)
{
	char	*tmp;

	tmp = increased_shlvl(shlvl_var);
	if (!tmp)
	{
		free_strs(new);
		exit(EXIT_FAILURE);
	}
	new[index] = ft_strdup(tmp);
	free(tmp);
	if (!new[index])
	{
		free_strs(new);
		exit(EXIT_FAILURE);
	}
	return (index + 1);
}

size_t	copy_other_var_env(char *other_var, char **new, size_t index)
{
	new[index] = ft_strdup(other_var);
	if (!new[index])
	{
		free_strs(new);
		exit(EXIT_FAILURE);
	}
	return (index + 1);
}

char	**copy_environnement(void)
{
	size_t	index;
	size_t	index2;
	char	**new;

	new = malloc(sizeof(char *) * (ft_strslen(environ) + 1));
	if (!new)
		return (NULL);
	index = 0;
	index2 = 0;
	while (environ[index])
	{
		new[index2] = NULL;
		if (ft_strncmp(environ[index], "SHLVL=", 6) == 0)
			index2 = copy_shlvl_var_env(environ[index], new, index2);
		else if (ft_strncmp(environ[index], "_=", 2) == 0)
			index2 = copy_underscore_var_env(new, index2);
		else
			index2 = copy_other_var_env(environ[index], new, index2);
		index++;
	}
	new[index2] = NULL;
	return (new);
}

char	*increased_shlvl(char *str)
{
	char	*new;
	int		shlvl;
	char	*tmp;

	shlvl = ft_atoi(str + 6);
	shlvl++;
	tmp = ft_itoa(shlvl);
	if (!tmp)
		return (NULL);
	new = ft_strjoin("SHLVL=", tmp);
	if (!new)
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (new);
}
