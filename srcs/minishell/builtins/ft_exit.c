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

#include "execution.h"
#include "builtins.h"
#include "environnement.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

int	is_number(char *str)
{
	int	index;

	index = 0;
	if (str[index] == '-' || str[index] == '+')
		index++;
	while (str[index])
	{
		if (str[index] < '0' || str[index] > '9')
			return (-1);
		index++;
	}
	return (0);
}

int	end_exit(t_exec *exec, t_node *node)
{
	decrease_shlvl(exec->envs);
	free_envs(exec->envs);
	clear_tree(node->head);
	reset_standard_streams(exec->fds);
	close_fds(exec->fds);
	exit(g_exit_status);
}

int	ft_exit(t_exec *exec, char **command, t_node *node)
{
	printf("exit WeShell\n");
	if (!command[1] || (ft_atol(command[1]) == 0 && is_number(command[1]) == 0))
	{
		printf("emprty exit\n");
		return (end_exit(exec, node));
	}
	else if (is_number(command[1]) == -1 || between_max_min(command[1]) == 1)
	{
		printf("WeShell: exit: %s: numeric argument required\n", command[1]);
		g_exit_status = 2;
		return (end_exit(exec, node));
	}
	else if (ft_strslen(command) > 2)
	{
		printf("WeShell: exit: too many arguments\n");
		g_exit_status = 127;
		return (g_exit_status);
	}
	else
	{
		g_exit_status = ft_atoi(command[1]);
		return (end_exit(exec, node));
	}
}
