/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:53:01 by dlacuey           #+#    #+#             */
/*   Updated: 2023/10/27 06:20:32 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "execution.h"
#include "fcntl.h"
#include <sys/wait.h>
#include <stdio.h>
#include "colors.h"

extern char	**environ;
extern int	exit_status;

void	exec_simple_command(t_node *node)
{
	char	**paths;
	char	*command;
	pid_t	pid1;

	if (!node->vector_strs.values)
		return ;
	pid1 = fork();
	if (pid1 < 0)
	{
		(exit_status = -1, perror(RED"Fork failed"));
		return ;
	}
	if (pid1 == 0)
	{
		paths = find_paths(environ);
		if (!paths)
		{
			(exit_status = -1, perror(RED"No paths found"));
			return ;
		}
		command = get_command(node->vector_strs.values[0], paths);
		if (!command)
		{
			(exit_status = -1, free_strs(paths), perror(RED"Command not found"));
			return ;
		}
		execve(command, node->vector_strs.values, environ);
		(exit_status = -1, free_strs(paths), free(command), perror(RED"Execve failed"));
		return ;
	}
	waitpid(pid1, &exit_status, 0);
}

void	redirection_output(t_node *node)
{
	int	fd;

	fd = open(node->right->vector_strs.values[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		(perror(RED"Open failed"), exit(1));
	if (dup2(fd, STDOUT_FILENO) < 0)
		(perror(RED"Dup2 failed"), exit(1));
	if (close(fd) < 0)
		(perror(RED"Close failed"), exit(1));
}

void	redirection_input(t_node *node)
{
	int	fd;

	fd = open(node->right->vector_strs.values[0], O_RDONLY);
	if (fd < 0)
		(perror(RED"Open failed"), exit(1));
	if (dup2(fd, STDIN_FILENO) < 0)
		(perror(RED"Dup2 failed"), exit(1));
	if (close(fd) < 0)
		(perror(RED"Close failed"), exit(1));
}

void	exec_full_command(t_node *node, int fds[3])
{
	if (node->type == COMMAND_I_REDIRECT)
	{
		redirection_input(node);
		if (!node->left)
			exec_full_command(node->right, fds);
		else
			exec_full_command(node->left, fds);
		dup2(fds[0], STDIN_FILENO);
	}
	else if (node->type == COMMAND_O_REDIRECT)
	{
		redirection_output(node);
		if (!node->left)
			exec_full_command(node->right, fds);
		else
			exec_full_command(node->left, fds);
		dup2(fds[1], STDOUT_FILENO);
	}
	else if (node->type == SIMPLE_COMMAND)
		exec_simple_command(node);
}

void	execution(t_node *tree)
{
	int fds[3];

	fds[1] = dup(1);
	fds[0] = dup(0);
	exec_full_command(tree, fds);
	close (fds[1]);
	close (fds[0]);
}
