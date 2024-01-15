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

int	ft_env(t_envs *envs)
{
	int	i;

	i = 0;
	while (envs->env[i])
	{
		printf("%s\n", envs->env[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
