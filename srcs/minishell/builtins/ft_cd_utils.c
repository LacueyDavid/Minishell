/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:45:13 by jdenis            #+#    #+#             */
/*   Updated: 2024/02/08 08:48:11 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	cd_point(bool pwd_exist, t_envs *envs, char *pwd)
{
	if (pwd_exist)
		ft_setenv("OLDPWD", pwd, envs);
	free(pwd);
}

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
	if (envs->env == NULL)
		return (NULL);
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
