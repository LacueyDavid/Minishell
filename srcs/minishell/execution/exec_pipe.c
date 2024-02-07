/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 04:36:12 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/07 17:37:31 by jdenis           ###   ########.fr       */
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

void	update_here_doc_index(t_node **node)
{
	(*node)->head->number_of_here_doc_index += how_many_heredocs((*node)->left);
}

static void	exec_pipe_except_last(t_node **node, t_exec *exec,
									t_pipe *pipe_utils, int *index)
{
	while ((*node)->type == COMMAND_PIPE)
	{
		pipe(pipe_utils->fds);
		pipe_utils->pids[*index] = fork();
		if (pipe_utils->pids[*index] < 0)
		{
			g_exit_status = -1;
			(perror(RED "Fork failed" WHITE), free(pipe_utils->pids));
			return ;
		}
		if (pipe_utils->pids[*index] == 0)
		{
			(free(pipe_utils->pids), dup2(pipe_utils->fds[1], STDOUT_FILENO));
			(close(pipe_utils->fds[0]), close(pipe_utils->fds[1]));
			(exec_full_command((*node)->left, exec), clear_tree((*node)->head));
			(free_envs(exec->envs));
			(reset_standard_streams(exec->fds), close_fds(exec->fds));
			exit(g_exit_status);
		}
		update_here_doc_index(node);
		dup2(pipe_utils->fds[0], STDIN_FILENO);
		(close(pipe_utils->fds[0]), close(pipe_utils->fds[1]));
		(*node) = (*node)->right;
		(*index)++;
	}
}

static void	exec_last_pipe(t_node *node, t_exec *exec,
							t_pipe *pipe_utils, int index)
{
	pipe_utils->pids[index] = fork();
	if (pipe_utils->pids[index] < 0)
	{
		g_exit_status = -1;
		(perror(RED "Fork failed" WHITE), free(pipe_utils->pids));
		return ;
	}
	if (pipe_utils->pids[index] == 0)
	{
		free(pipe_utils->pids);
		exec_full_command(node, exec);
		(clear_tree(node->head), free_envs(exec->envs));
		reset_standard_streams(exec->fds);
		close_fds(exec->fds);
		exit(g_exit_status);
	}
}

void	exec_pipes(t_node *node, t_exec *exec)
{
	t_pipe	pipe_utils;
	int		index;

	index = 0;
	pipe_utils.pids = malloc(sizeof(pid_t) * (node->number_of_pipes + 1));
	if (!pipe_utils.pids)
	{
		g_exit_status = -1;
		perror(RED "Malloc failed" WHITE);
		return ;
	}
	(signal(SIGINT, SIG_IGN), signal(SIGQUIT, SIG_IGN));
	exec_pipe_except_last(&node, exec, &pipe_utils, &index);
	exec_last_pipe(node, exec, &pipe_utils, index);
	dup2(exec->fds[0], STDIN_FILENO);
	(close(pipe_utils.fds[0]), close(pipe_utils.fds[1]));
	(signal(SIGINT, handler_sigint), signal(SIGQUIT, handler_sigquit));
	(wait_all_pids(pipe_utils.pids, index), free(pipe_utils.pids));
}
