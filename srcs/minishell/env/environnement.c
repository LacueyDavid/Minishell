/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:06:05 by jdenis            #+#    #+#             */
/*   Updated: 2023/12/11 06:29:15 by marvin           ###   ########.fr       */
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

char	**copy_environnement()
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
		return NULL;
	while (environ[index])
	{
		new[index] = ft_strdup(environ[index]);
		if (!new[index])
		{
			free_strs(new);
			return NULL;
		}
		index++;
	}
	new[index] = NULL;
	return (new);
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

char	*ft_strdup_with_quotes(char *str)
{
	char	*new;
	size_t	index;
	size_t	index2;

	index = 0;
	index2 = 0;
	//je comprends pas pourquoi je dois mettre le fois 2, mais sinon ca marche pas
	new = malloc(sizeof(char) * (2 * ft_strlen(str) + 3));
	if (!new)
		return NULL;
	while (str[index])
	{
		new[index2] = str[index];
		if (str[index] == '=')
		{
			index2++;
			new[index2] = '"';
		}
		index++;
		index2++;
	}
	new[index2] = '"';
	new[index2 + 1] = '\0';
	return (new);
}

//pour pouvoir faire un export seul, difference : c'est dans l'ordre alphabetique, avec la valeur des variables entre doubel quotes et on ne prend pas les _=/usr/bin/env
char **copy_env_export()
{
	size_t	index;
	size_t	index2;
	size_t	length;
	char 	**new;

	length = 0;
	index = 0;
	index2 = 0;
	while (environ[length])
		length++;
	new = malloc(sizeof(char *) * (length));
	if (!new)
		return NULL;
	while (environ[index])
	{
		if (!(environ[index][0] == '_' && environ[index][1] == '='))
		{
			new[index2] = ft_strdup_with_quotes(environ[index]);
			if (!new[index2])
			{
				free_strs(new);
				return NULL;
			}
			index2++;
		}
		index++;
	}
	new[index2] = NULL;
	sort(new);
	return (new);
}

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

int main(void)
{
	t_envs	*envs;
	size_t	index;

	index = 0;
	envs = copy_env_and_export();
	printf("print de l'env\n");
	while (envs->env[index])
	{
		printf("%s\n", envs->env[index]);
		index++;
	}
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");

	printf("print de l'export\n");
	index = 0;
	while (envs->exports[index])
	{
		printf("%s\n", envs->exports[index]);
		index++;
	}
	free_envs(envs);
	return (0);

}