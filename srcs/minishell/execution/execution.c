/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:53:01 by dlacuey           #+#    #+#             */
/*   Updated: 2023/11/30 16:52:43 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "execution.h"
#include "fcntl.h"
#include <sys/wait.h>
#include <stdio.h>
#include "colors.h"
#include "get_next_line.h"
#include <readline/readline.h>
#include "wildcards.h"
#include <sys/types.h>
#include <unistd.h>

extern char	**environ;
extern int	exit_status;

void	exec_in_the_son(t_node *node)
{
	char	**paths;
	char	*command;

	paths = find_paths(environ);
	if (!paths)
	{
		(exit_status = -1, perror(RED"No paths found"WHITE));
		return ;
	}
	command = get_command(node->vector_strs.values[0], paths);
	if (!command)
	{
		(exit_status = -1, free_strs(paths), perror(RED"Command not found"WHITE));
		return ;
	}
	wildcards(&(node->vector_strs.values));
	if (!node->vector_strs.values)
	{
		(exit_status = -1, free_strs(paths), perror(RED"Wildcards failed"));
		return ;
	}
	execve(command, node->vector_strs.values, environ);
	(exit_status = -1, free_strs(paths), free(command), perror(RED"Execve failed"WHITE));
	return ;
}

void	exec_simple_command(t_node *node)
{
	pid_t	pid1;

	if (!node || !node->vector_strs.values)
		return ;
	pid1 = fork();
	if (pid1 < 0)
	{
		(exit_status = -1, perror(RED"Fork failed"WHITE));
		return ;
	}
	if (pid1 == 0)
	{
		exec_in_the_son(node);
		return ;
	}
	waitpid(pid1, &exit_status, 0);
}

void	exec_full_command(t_node *node, t_exec_map exec_map[NUMBER_OF_EXEC_FUNCS])
{
	if (!node)
		return ;
	exec_map[node->type].function(node);
	if (node->type != SIMPLE_COMMAND)
	{
		if (!node->left)
			exec_full_command(node->right, exec_map);
		else
			exec_full_command(node->left, exec_map);
	}
	unlink("here_doc.minishell");
}

void exec_pipes(t_node *node, t_exec_map exec_map[NUMBER_OF_EXEC_FUNCS])
{
	int		fds[2];
	int		fd_stdin;
	pid_t	*pids;
	int		index;
	int		index2;

	index = 0;
	index2 = 0;
	fd_stdin = dup(STDIN_FILENO);
	pids = malloc(sizeof(pid_t) * (node->number_of_pipes + 1));
	if (!pids)
	{
		(exit_status = -1, perror(RED"Malloc failed"WHITE));
		return ;
	}
	while (node->type == COMMAND_PIPE)
	{
		pipe(fds);
		pids[index] = fork();
		if (pids[index] < 0)
		{
			(exit_status = -1, perror(RED"Fork failed"WHITE));
			return ;
		}
		if (pids[index] == 0)
		{
			dup2(fds[1], STDOUT_FILENO);
			close(fd_stdin);
			close(fds[0]);
			close(fds[1]);
			exec_full_command(node->left, exec_map);
			free(pids);
			clear_tree(node->head);
			exit(exit_status);
		}
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
		close(fds[1]);
		node = node->right;
		index++;
	}
	pids[index] = fork();
	if (pids[index] < 0)
	{
		(exit_status = -1, perror(RED"Fork failed"WHITE));
		return ;
	}
	if (pids[index] == 0)
	{
		close(fd_stdin);
		close(fds[0]);
		close(fds[1]);
		exec_full_command(node, exec_map);
		free(pids);
		clear_tree(node->head);
		exit(exit_status);
	}
	while (index2 <= index)
	{
		waitpid(pids[index2], &exit_status, 0);
		index2++;
	}
	free(pids);
	dup2(fd_stdin, STDIN_FILENO);
	close(fd_stdin);
	close(fds[0]);
	close(fds[1]);
}

void	execution(t_node *tree)
{
	int fds[NUMBER_OF_FDS];
	t_exec_map	exec_map[NUMBER_OF_EXEC_FUNCS];

	init_fds(fds);
	init_exec_func_map(exec_map);
	if (tree->number_of_pipes > 0)
		exec_pipes(tree, exec_map);
	else
		exec_full_command(tree, exec_map);
	reset_standard_streams(fds);
	close_fds(fds);
}
