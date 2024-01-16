/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:53:01 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/16 04:59:55 by dlacuey          ###   ########.fr       */
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

void	exec_in_the_son(t_node *node, t_envs *envs)
{
	(signal(SIGINT, SIG_DFL), signal(SIGQUIT, SIG_DFL));
	wildcards(&(node->vector_strs.values));
	wildcards_fail_protection(node);
	if (!expand_env_variables(&(node->vector_strs), envs))
		expand_fail_protection(node);
	if (!node->vector_strs.values)
		vector_null_protection(node);
	if (is_a_builtin(node->vector_strs.values[0]))
		do_builtins(node, envs);
	else
		do_execve(node, envs);
}

void	exec_simple_command(t_node *node, t_envs *envs)
{
	pid_t	pid1;

	if (!node || !node->vector_strs.values)
		return ;
	pid1 = fork();
	if (pid1 < 0)
	{
		g_exit_status = -1;
		perror(RED "Fork failed" WHITE);
		return ;
	}
	if (pid1 == 0)
		exec_in_the_son(node, envs);
	waitpid(pid1, &g_exit_status, 0);
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	else if (WIFSIGNALED(g_exit_status))
		g_exit_status = WTERMSIG(g_exit_status) + 128;
}

void	exec_full_command(t_node *node, t_exec *exec)
{
	if (!node)
		return ;
	(signal(SIGINT, handler_sigint), signal(SIGQUIT, handler_sigint));
	if (node->type == HERE_DOCUMENT)
		do_here_doc(node);
	else if (node->type == SIMPLE_COMMAND)
		exec_simple_command(node, exec->envs);
	else
		exec->exec_map[node->type].function(node);
	if (node->type != SIMPLE_COMMAND)
	{
		if (!node->left)
			exec_full_command(node->right, exec);
		else
			exec_full_command(node->left, exec);
	}
}

void	execution(t_node *tree, t_envs *envs)
{
	t_exec	exec;

	(signal(SIGINT, handler_sigint), signal(SIGQUIT, handler_sigint));
	init_exec(&exec, envs);
	fork_heredocs(tree, exec.fds);
	if (tree->number_of_pipes > 0)
		exec_pipes(tree, &exec);
	else
		exec_full_command(tree, &exec);
	reset_standard_streams(exec.fds);
	close_fds(exec.fds);
	unlink_heredoc_files(tree);
}
