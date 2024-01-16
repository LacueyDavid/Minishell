/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builtin_or_execve.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 04:40:33 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/16 04:59:05 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "colors.h"
#include "environnement.h"
#include "execution.h"
#include "get_next_line.h"
#include "here_doc.h"
#include "libft.h"
#include "minishell_signals.h"
#include "wildcards.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

extern char	**environ;
extern int	g_exit_status;

void	do_builtins(t_node *node, t_envs *envs)
{
	g_exit_status = exec_builtin(node->vector_strs.values, envs);
	if (g_exit_status == -1)
		perror(RED "Exec builtins failed" WHITE);
	clear_tree(node->head);
	free_envs(envs);
	exit(g_exit_status);
}

void	do_execve(t_node *node, t_envs *envs)
{
	char	*command;
	char	**paths;

	paths = find_paths(environ);
	if (!paths)
		path_fail_protection(node);
	command = get_command(node->vector_strs.values[0], paths);
	free_strs(paths);
	if (!command)
	{
		clear_tree(node->head);
		exit(g_exit_status);
	}
	execve(command, node->vector_strs.values, envs->env);
	free_envs(envs);
	g_exit_status = -1;
	(free(command), free_envs(envs)),
	perror(RED "Execve failed" WHITE);
	clear_tree(node->head);
	exit(g_exit_status);
}
