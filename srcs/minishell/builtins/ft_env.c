/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/12/04 12:18:50 by marvin            #+#    #+#             */
/*   Updated: 2023/12/04 12:18:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environnement.h"
#include <stdio.h>
#include <stdlib.h>

extern int	g_exit_status;

int	ft_env(t_envs *envs, char **command)
{
	int	i;

	if (!envs->env)
		return (EXIT_FAILURE);
	i = 0;
	if (command[1])
	{
		printf("env: \'%s\': Permission denied\n", command[1]);
		g_exit_status = 126;
		return (EXIT_FAILURE);
	}
	while (envs->env[i])
	{
		printf("%s\n", envs->env[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
