/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 08:07:24 by jdenis            #+#    #+#             */
/*   Updated: 2024/02/08 08:31:34 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "environnement.h"
#include "libft.h"
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

extern int	g_exit_status;

bool	is_a_builtin(char *command)
{
	if (!command)
		return (false);
	if (!ft_strcmp(command, "echo"))
		return (true);
	if (!ft_strcmp(command, "cd"))
		return (true);
	if (!ft_strcmp(command, "pwd"))
		return (true);
	if (!ft_strcmp(command, "export"))
		return (true);
	if (!ft_strcmp(command, "unset"))
		return (true);
	if (!ft_strcmp(command, "env"))
		return (true);
	if (!ft_strcmp(command, "exit"))
		return (true);
	return (false);
}

char	*ft_compact_strs(char **strs)
{
	char	*string;
	size_t	size;
	size_t	index;

	index = 0;
	size = 0;
	while (strs[index])
	{
		size += ft_strlen(strs[index]);
		index++;
	}
	string = malloc(sizeof(char) * (size * 2));
	if (!string)
		return (NULL);
	string[0] = '\0';
	index = 0;
	while (strs[index])
	{
		ft_strlcat(string, strs[index], ft_strlen(string)
			+ ft_strlen(strs[index]) + 1);
		if (strs[index + 1])
			ft_strcat(string, " ");
		index++;
	}
	return (string);
}

int	exec_builtin(char **command, t_exec *exec, t_node *node)
{
	int		g_exit_status;
	char	*string_command;

	g_exit_status = EXIT_FAILURE;
	string_command = NULL;
	string_command = ft_compact_strs(command);
	if (!string_command)
		return (EXIT_FAILURE);
	if (!ft_strcmp(command[0], "cd"))
		g_exit_status = ft_cd(exec->envs, string_command);
	free(string_command);
	if (!ft_strcmp(command[0], "echo"))
		g_exit_status = ft_echo(command);
	if (!ft_strcmp(command[0], "pwd"))
		g_exit_status = ft_pwd(exec->envs);
	if (!ft_strcmp(command[0], "export"))
		g_exit_status = ft_export(exec->envs, command);
	if (!ft_strcmp(command[0], "unset"))
		g_exit_status = ft_unset(exec->envs, command);
	if (!ft_strcmp(command[0], "env"))
		g_exit_status = ft_env(exec->envs, command);
	if (!ft_strcmp(command[0], "exit"))
		g_exit_status = ft_exit(exec, command, node);
	return (g_exit_status);
}
