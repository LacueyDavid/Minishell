/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:45:13 by jdenis            #+#    #+#             */
/*   Updated: 2024/01/16 18:52:24 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*ft_strcat(char *dest, char *src)
{
	int	index;
	int	index2;

	index = 0;
	if (dest == NULL || src == NULL)
		return (NULL);
	while (dest[index] != '\0')
		index++;
	index2 = 0;
	while (src[index2] != '\0')
	{
		dest[index + index2] = src[index2];
		index2++;
	}
	dest[index + index2] = '\0';
	return (dest);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	index;

	index = 0;
	if (dest == NULL || src == NULL)
		return (NULL);
	while (src[index] != '\0')
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = '\0';
	return (dest);
}

char	*ft_getenv(char *name, t_envs *envs)
{
	size_t	index;
	size_t	length;
	char	*value;

	index = 0;
	length = ft_strlen(name);
	while (envs->env[index])
	{
		if (!ft_strncmp(envs->env[index], name, length))
		{
			value = ft_strdup(envs->env[index] + length + 1);
			return (value);
		}
		index++;
	}
	return (NULL);
}

void	ft_setenv(char *name, char *value, t_envs *envs)
{
	size_t	index;
	size_t	length;

	index = 0;
	length = ft_strlen(name);
	while (envs->env[index])
	{
		if (ft_strncmp(envs->env[index], name, length) == 0)
		{
			free(envs->env[index]);
			envs->env[index] = malloc(sizeof(char) * (length + ft_strlen(value)
						+ 2));
			ft_strcpy(envs->env[index], name);
			ft_strcat(envs->env[index], "=");
			ft_strcat(envs->env[index], value);
			return ;
		}
		index++;
	}
}

void	change_pwd_in_env(char *path, t_envs *envs)
{
	char	*current_pwd;

	current_pwd = ft_getenv("PWD", envs);
	ft_setenv("OLDPWD", current_pwd, envs);
	ft_setenv("PWD", path, envs);
	free(current_pwd);
}
