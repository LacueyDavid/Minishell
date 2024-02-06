/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builtin_or_execve.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 04:40:33 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/06 16:52:27 by dlacuey          ###   ########.fr       */
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

extern int	g_exit_status;

void	exec_non_builtin_command(t_node *node, t_envs *envs)
{
	(signal(SIGINT, SIG_DFL), signal(SIGQUIT, SIG_DFL));
	wildcards(&(node->vector_strs.values));
	wildcards_fail_protection(node, envs);
	if (!expand_env_variables(&(node->vector_strs), envs))
		expand_fail_protection(node, envs);
	if (!node->vector_strs.values)
		vector_null_protection(node, envs);
	// if (is_a_builtin(node->vector_strs.values[0]))
	// 	do_builtins(node, envs);
	// else
	do_execve(node, envs);
}

void	exec_builtin_command(t_node *node, t_envs *envs)
{
	if (!node || !node->vector_strs.values)
		return ;
	(signal(SIGINT, SIG_DFL), signal(SIGQUIT, SIG_DFL));
	wildcards(&(node->vector_strs.values));
	wildcards_fail_protection(node, NULL);
	if (!expand_env_variables(&(node->vector_strs), envs))
		expand_fail_protection(node, NULL);
	if (!node->vector_strs.values)
		vector_null_protection(node, NULL);
	do_builtins(node, envs);
}

void	do_builtins(t_node *node, t_envs *envs)
{
	g_exit_status = exec_builtin(node->vector_strs.values, envs, node);
	if (g_exit_status == -1)
		perror(RED "Exec builtins failed" WHITE);
}

void	do_execve(t_node *node, t_envs *envs)
{
	char	*command;
	char	**paths;

	paths = find_paths(envs->env);
	command = get_command(node->vector_strs.values[0], paths);
	free_strs(paths);
	if (!command)
	{
		(clear_tree(node->head));
		free_envs(envs);
		exit(g_exit_status);
	}
	execve(command, node->vector_strs.values, envs->env);
	g_exit_status = -1;
	(free(command), free_envs(envs), clear_tree(node->head));
	perror(RED "Execve failed" WHITE);
	exit(g_exit_status);
}
