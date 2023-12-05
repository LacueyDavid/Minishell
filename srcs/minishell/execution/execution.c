/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:53:01 by dlacuey           #+#    #+#             */
/*   Updated: 2023/12/05 23:07:36 by dlacuey          ###   ########.fr       */
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
		clear_tree(node->head);
		exit(exit_status);
	}
	command = get_command(node->vector_strs.values[0], paths);
	free_strs(paths);
	if (!command)
	{
		(exit_status = 127, fprintf(stderr, RED"-Wesh: %s: command not found\n"WHITE, node->vector_strs.values[0]));
		clear_tree(node->head);
		exit(exit_status);
	}
	wildcards(&(node->vector_strs.values));
	if (!node->vector_strs.values)
	{
		(exit_status = 134, perror(RED"Wildcards failed"));
		clear_tree(node->head);
		exit(exit_status);
	}
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	execve(command, node->vector_strs.values, environ);
	(exit_status = -1, free(command), perror(RED"Execve failed"WHITE));
	clear_tree(node->head);
	exit(exit_status);
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
		exec_in_the_son(node);
	waitpid(pid1, &exit_status, 0);
	if (WIFEXITED(exit_status))
		exit_status = WEXITSTATUS(exit_status);
}

void	exec_full_command(t_node *node, t_exec_map exec_map[NUMBER_OF_EXEC_FUNCS], int fds[NUMBER_OF_FDS])
{
	if (!node)
		return ;
	if (node->type == HERE_DOCUMENT)
	{
		dup2(fds[0], STDIN_FILENO);
		dup2(fds[1], STDOUT_FILENO);
	}
	exec_map[node->type].function(node);
	if (node->type != SIMPLE_COMMAND)
	{
		if (!node->left)
			exec_full_command(node->right, exec_map, fds);
		else
			exec_full_command(node->left, exec_map, fds);
	}
	// if (node->type == SIMPLE_COMMAND)
	// 	dup2(fd_stdin, STDIN_FILENO);
	unlink("here_doc.minishell");
}

void exec_pipes(t_node *node, t_exec_map exec_map[NUMBER_OF_EXEC_FUNCS], int fds[NUMBER_OF_FDS])
{
	int		pipe_fds[2];
	pid_t	*pids;
	int		index;
	int		index2;

	index = 0;
	index2 = 0;
	pids = malloc(sizeof(pid_t) * (node->number_of_pipes + 1));
	if (!pids)
	{
		(exit_status = -1, perror(RED"Malloc failed"WHITE));
		return ;
	}
	while (node->type == COMMAND_PIPE)
	{
		pipe(pipe_fds);
		pids[index] = fork();
		if (pids[index] < 0)
		{
			(exit_status = -1, perror(RED"Fork failed"WHITE));
			free(pids);
			return ;
		}
		if (pids[index] == 0)
		{
			free(pids);
			dup2(pipe_fds[1], STDOUT_FILENO);
			close(pipe_fds[0]);
			close(pipe_fds[1]);
			exec_full_command(node->left, exec_map, fds);
			clear_tree(node->head);
			exit(0);
		}
		dup2(pipe_fds[0], STDIN_FILENO);
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		node = node->right;
		index++;
	}
	pids[index] = fork();
	if (pids[index] < 0)
	{
		(exit_status = -1, perror(RED"Fork failed"WHITE));
		free(pids);
		return ;
	}
	if (pids[index] == 0)
	{
		free(pids);
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		exec_full_command(node, exec_map, fds);
		clear_tree(node->head);
		exit(0);
	}
	dup2(fds[0], STDIN_FILENO);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	while (index2 <= index)
	{
		waitpid(pids[index2], &exit_status, 0);
		if (WIFEXITED(exit_status))
			exit_status = WEXITSTATUS(exit_status);
		index2++;
	}
	free(pids);
}

static void	handler_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	execution(t_node *tree)
{
	int fds[NUMBER_OF_FDS];
	t_exec_map	exec_map[NUMBER_OF_EXEC_FUNCS];

	signal(SIGINT, handler_sigint);
	signal(SIGQUIT, handler_sigint);
	init_fds(fds);
	init_exec_func_map(exec_map);
	if (tree->number_of_pipes > 0)
		exec_pipes(tree, exec_map, fds);
	else
		exec_full_command(tree, exec_map, fds);
	reset_standard_streams(fds);
	close_fds(fds);
}
