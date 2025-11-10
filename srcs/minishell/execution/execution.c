/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:53:01 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/07 12:58:33 by dlacuey          ###   ########.fr       */
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

void	exec_simple_command(t_node *node, t_exec *exec)
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
		exec_non_builtin_command(node, exec);
	waitpid(pid1, &g_exit_status, 0);
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	else if (WIFSIGNALED(g_exit_status))
		g_exit_status = WTERMSIG(g_exit_status) + 128;
}

static void	redo_full_command(t_node *node, t_exec *exec)
{
	if (node->type != SIMPLE_COMMAND)
	{
		if (!node->left)
			exec_full_command(node->right, exec);
		else
			exec_full_command(node->left, exec);
	}
}

void	exec_full_command(t_node *node, t_exec *exec)
{
	bool	catch;

	catch = false;
	if (!node)
		return ;
	if (node->type == HERE_DOCUMENT)
		do_here_doc(node);
	else if (node->type == SIMPLE_COMMAND && node->vector_strs.values
		&& is_a_builtin(node->vector_strs.values[0]))
		exec_builtin_command(node, exec);
	else if (node->type == SIMPLE_COMMAND)
		exec_simple_command(node, exec);
	else
	{
		if (!protect_redirection(node->right, exec))
			return ;
		catch = exec->exec_map[node->type].function(node);
		if (!catch)
			return ;
	}
	redo_full_command(node, exec);
}

void	execution(t_node *tree, t_envs *envs)
{
	t_exec	exec;

	(signal(SIGINT, handler_sigint), signal(SIGQUIT, handler_sigquit));
	init_exec(&exec, envs);
	fork_heredocs(tree, exec.fds);
	if (g_exit_status == 4444)
	{
		reset_standard_streams(exec.fds);
		close_fds(exec.fds);
		unlink_heredoc_files(tree);
		return ;
	}
	(signal(SIGINT, handler_sigint), signal(SIGQUIT, handler_sigquit));
	if (tree->number_of_pipes > 0)
		exec_pipes(tree, &exec);
	else
		exec_full_command(tree, &exec);
	(signal(SIGINT, handler_sigint), signal(SIGQUIT, handler_sigquit));
	reset_standard_streams(exec.fds);
	close_fds(exec.fds);
	unlink_heredoc_files(tree);
}
