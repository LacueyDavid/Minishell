/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/12/04 12:27:18 by marvin            #+#    #+#             */
/*   Updated: 2023/12/04 12:27:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "environnement.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

extern int	g_exit_status;

void	decrease_shlvl(t_envs *envs)
{
	char	*shlvl;
	int		shlvl_int;
	char	*shlvl_str;

	shlvl = ft_getenv("SHLVL", envs);
	if (!shlvl)
		return ;
	shlvl_int = ft_atoi(shlvl);
	shlvl_int--;
	shlvl_str = ft_itoa(shlvl_int);
	ft_setenv("SHLVL", shlvl_str, envs);
	free(shlvl);
	free(shlvl_str);
}

int	ft_exit(t_envs *envs, char *status)
{
	if (!status || ft_atoi(status + 5) == 0)
		g_exit_status = 0;
	else
		g_exit_status = ft_atoi(status + 5);
	printf("exit WeShell\n");
	decrease_shlvl(envs);
	redo_envs(envs);
	return (g_exit_status);
}
