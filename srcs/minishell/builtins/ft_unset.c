/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 08:20:49 by jdenis            #+#    #+#             */
/*   Updated: 2024/02/08 09:00:38 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environnement.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	remove_environment_variable(char **envs, char *variable_name)
{
	size_t	index;
	size_t	length;

	index = 0;
	length = ft_strlen(variable_name);
	while (envs[index])
	{
		if (strncmp(envs[index], variable_name, length) == 0
			&& (envs[index][length] == '=' || envs[index][length] == '\0'))
		{
			free(envs[index]);
			while (envs[index] != NULL)
			{
				envs[index] = envs[index + 1];
				++index;
			}
			break ;
		}
		++index;
	}
}

int	ft_unset(t_envs *envs, char **input)
{
	size_t	index;

	index = 1;
	if (!envs || envs->env == NULL || envs->exports == NULL)
		return (EXIT_FAILURE);
	while (input[index])
	{
		remove_environment_variable(envs->env, input[index]);
		remove_environment_variable(envs->exports, input[index]);
		index++;
	}
	return (EXIT_SUCCESS);
}
