/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement_utils_3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:47:03 by jdenis            #+#    #+#             */
/*   Updated: 2024/01/22 17:28:44 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environnement.h"
#include "builtins.h"

extern char	**environ;

void	update_envs(t_envs *envs)
{
	update_env(envs);
	update_export(envs);
}

void	free_envs(t_envs *envs)
{
	free_strs(envs->env);
	free_strs(envs->exports);
	free(envs);
}

char	**copy_environnement(void)
{
	size_t	index;
	size_t	length;
	char	**new;

	length = 0;
	index = 0;
	while (environ[length])
		length++;
	new = malloc(sizeof(char *) * (length + 1));
	if (!new)
		return (NULL);
	while (environ[index])
	{
		new[index] = ft_strdup(environ[index]);
		if (!new[index])
		{
			free_strs(new);
			return (NULL);
		}
		index++;
	}
	new[index] = NULL;
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
