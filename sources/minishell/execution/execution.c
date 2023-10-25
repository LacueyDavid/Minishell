/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:53:01 by dlacuey           #+#    #+#             */
/*   Updated: 2023/10/25 09:50:14 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "execution.h"
#include "fcntl.h"
#include <sys/wait.h>
#include <stdio.h>

extern char	**environ;
extern int	exit_status;

void	exec_simple_command(t_node *node)
{
	char	**paths;
	char	*command;
	pid_t	pid1;

	if (!node->values)
		return ;
	pid1 = fork();
	if (pid1 < 0)
	{
		(perror("Fork failed"));
		return ;
	}
	if (pid1 == 0)
	{
		paths = find_paths(environ);
		if (!paths)
		{
			clear_tree(node->head);
			return ;
		}
		command = get_command(node->values[0], paths);
		if (!command)
		{
			free_strs(paths);
			clear_tree(node->head);
			(perror("Command not found"), exit(1));
		}
		execve(command, node->values, environ);
		free_strs(paths);
		clear_tree(node->head);
		(perror("Execve failed"), exit(1));
	}
	waitpid(pid1, &exit_status, 0);
}

void	redirection_output(t_node *node)
{
	int	fd;

	fd = open(node->right->values[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		(perror("Open failed"), exit(1));
	if (dup2(fd, STDOUT_FILENO) < 0)
		(perror("Dup2 failed"), exit(1));
	if (close(fd) < 0)
		(perror("Close failed"), exit(1));
}

void	exec_full_command(t_node *node, int fds[3])
{
	if (node->type == O_REDIRECTION)
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
	exec_full_command(tree, fds);
	close (fds[1]);
}
