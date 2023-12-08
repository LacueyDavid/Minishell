/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 08:20:49 by jdenis            #+#    #+#             */
/*   Updated: 2023/12/07 08:37:10 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"

extern char **environ;

void remove_environment_variable(char *variable_name) 
{
    size_t	index;
    size_t	length;

	index = 0;
	length = ft_strlen(variable_name);
    while (environ[index]) 
	{
        if (strncmp(environ[index], variable_name, length) == 0 && environ[index][length] == '=') 
		{
            while (environ[index] != NULL) {
                environ[index] = environ[index + 1];
                ++index;
            }
            break;
        }
		++index;
    }
}

int	ft_unset(char **input) 
{
    size_t	index;

	index = 1;
	while (input[index])
    {
		remove_environment_variable(input[index]);
		index++;
	}
    return (EXIT_SUCCESS);
}
