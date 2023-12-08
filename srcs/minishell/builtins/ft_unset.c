/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 08:20:49 by jdenis            #+#    #+#             */
/*   Updated: 2023/12/08 13:54:36 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"
#include "environnement.h"

void remove_environment_variable(char **envs, char *variable_name) 
{
    size_t	index;
    size_t	length;

	index = 0;
	length = ft_strlen(variable_name);
    while (envs[index]) 
	{
        if (strncmp(envs[index], variable_name, length) == 0 && envs[index][length] == '=') 
		{
            while (envs[index] != NULL) {
                envs[index] = envs[index + 1];
                ++index;
            }
            break;
        }
		++index;
    }
}

int	ft_unset(t_envs *envs, char **input) 
{
    size_t	index;

	index = 1;
	while (input[index])
    {
		remove_environment_variable(envs->env, input[index]);
        remove_environment_variable(envs->exports, input[index]);
		index++;
	}
    return (EXIT_SUCCESS);
}
