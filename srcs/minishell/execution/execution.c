/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:53:01 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/05 19:19:43 by dlacuey          ###   ########.fr       */
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
	wildcards_fail_protection(node, envs);
	if (!expand_env_variables(&(node->vector_strs), envs))
		expand_fail_protection(node, envs);
	if (!node->vector_strs.values)
		vector_null_protection(node, envs);
	if (is_a_builtin(node->vector_strs.values[0]))
		do_builtins(node, envs);
	else
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

static bool	protect_redirection(t_node *node, t_envs *envs)
{
	if (!expand_env_variables(&(node->vector_strs), envs))
		return (false);
	if (node->vector_strs.values)
		if (!node->vector_strs.values[0])
			return (perror(RED "wesh: ambiguous redirect" WHITE), false);
	return (true);
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
		exec_builtin_command(node, exec->envs);
	else if (node->type == SIMPLE_COMMAND)
		exec_simple_command(node, exec->envs);
	else
	{
		if (!protect_redirection(node->right, exec->envs))
			return ;
		catch = exec->exec_map[node->type].function(node);
		if (!catch)
			return ;
	}
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

	(signal(SIGINT, handler_sigint), signal(SIGQUIT, handler_sigquit));
	init_exec(&exec, envs);
	fork_heredocs(tree, exec.fds);
	if (g_exit_status == 4444)
	{
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
