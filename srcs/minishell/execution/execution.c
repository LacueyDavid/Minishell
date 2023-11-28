/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:53:01 by dlacuey           #+#    #+#             */
/*   Updated: 2023/11/28 03:23:48 by dlacuey          ###   ########.fr       */
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

void	exec_full_command(t_node *node, int fds[NUMBER_OF_FDS], t_exec_map exec_map[NUMBER_OF_EXEC_FUNCS])
{
	if (!node)
		return ;
	exec_map[node->type].function(node);
	if (node->type != SIMPLE_COMMAND)
	{
		if (!node->left)
			exec_full_command(node->right, fds, exec_map);
		else
			exec_full_command(node->left, fds, exec_map);
	}
	reset_standard_streams(fds);
	unlink("here_doc.minishell");
}

void exec_pipes(t_node *node, t_exec_map exec_map[NUMBER_OF_EXEC_FUNCS])
{
	int		**pipe_fds;
	pid_t	*pid_tab;
	size_t	index;

	index = 0;
	pipe_fds = malloc(sizeof(int *) * node->number_of_pipes + 1);
	pid_tab = malloc(sizeof(pid_t) * (node->number_of_pipes + 1));
	if (!pipe_fds || !pid_tab)
	{
		perror(RED"Malloc failed"WHITE);
		exit(EXIT_FAILURE);
	}
	// Create pipes
	while (index < node->number_of_pipes + 1)
	{
		pipe_fds[index] = malloc(sizeof(int) * 2);
		if (!pipe_fds[index])
		{
			perror(RED"Malloc failed"WHITE);
			//supp tout les malloc si un malloc fail
			exit(EXIT_FAILURE);
		}
		if (pipe(pipe_fds[index]) < 0)
		{
			perror(RED"Pipe failed"WHITE);
			exit(EXIT_FAILURE);
		}
		index++;
	}
	index = 0;
	pid_tab[index] = fork();
	if (pid_tab[index] < 0)
	{
		perror(RED"Fork failed"WHITE);
		exit(EXIT_FAILURE);
	}
	index++;
	while (index < node->number_of_pipes + 1)
	{
		if(pid_tab[0] == 0)
		{
			pid_tab[index] = fork();
			if (pid_tab[index] < 0)
			{
				perror(RED"Fork failed"WHITE);
				exit(EXIT_FAILURE);
			}
		}
		index++;
	}
	printf("number of pipes : %zu\n", node->number_of_pipes);
	while (index < node->number_of_pipes + 1)
	{
		if (pid_tab[index] == 0)
		{
			if (index == 0)
			{
				dup2(pipe_fds[index][0], STDIN_FILENO);
				dup2(pipe_fds[index][1], 3);
				printf("je suis le premier fork\n");
				exec_full_command(node->left, pipe_fds[index], exec_map);
				close(pipe_fds[index][0]);
				close(pipe_fds[index][1]);
			}
			else if (index == node->number_of_pipes)
			{
				dup2(pipe_fds[index][1], STDOUT_FILENO);
				dup2(pipe_fds[index][0], node->number_of_pipes + 2);
				printf("je suis le dernier fork\n");
				exec_full_command(node->right, pipe_fds[index], exec_map);
				close(pipe_fds[index][1]);
				close(pipe_fds[index][0]);
			}
			else
			{
				dup2(pipe_fds[index][0], (int)index + 2);
				dup2(pipe_fds[index][1], (int)index + 3);
				printf("je suis le fork numero %zu\n", index);
				exec_full_command(node->left, pipe_fds[index], exec_map);
				close(pipe_fds[index][0]);
				close(pipe_fds[index][1]);
			}
		}
		index++;
		if (node->type == COMMAND_PIPE && node->right->type == COMMAND_PIPE)
			node = node->right;
	}
	// Close all pipe ends in the parent process
	index = 0;
	while (index < node->number_of_pipes)
	{
		close(pipe_fds[index][0]);
		close(pipe_fds[index][1]);
		index++;
	}
	// Wait for all child processes to finish
	index = 0;
	while (index < node->number_of_pipes + 1)
	{
		waitpid(pid_tab[index], &exit_status, 0);
		index++;
	}
	// Clean up
	index = 0;
	while (index < node->number_of_pipes + 1)
	{
		free(pipe_fds[index]);
		index++;
	}
	free(pipe_fds);
	free(pid_tab);
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
		exec_full_command(tree, fds, exec_map);
	close_fds(fds);
}
