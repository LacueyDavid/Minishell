/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:53:01 by dlacuey           #+#    #+#             */
/*   Updated: 2023/10/18 04:55:51 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "libft.h"
#include "execution.h"
#include "fcntl.h"

extern char	**environ;

void	exec_simple_command(char **value)
{
	pid_t	pid1;
	char	**paths;
	char	*command;

	paths = find_paths(environ);
	command = get_command(value[0], paths);
	pid1 = fork();
	if (pid1 == 0)
		execve(command, value, environ);
	waitpid(pid1, NULL, 0);
}

void	redirection_output(t_node *node)
{
	int	fd;

	fd = open(node->right->value[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd, 1);
	close(fd);
}

void	exec_full_command(t_node *node)
{
	if (node->type == O_REDIRECTION)
	{
		redirection_output(node);
		exec_full_command(node->left);
	}
	else if (node->type == SIMPLE_COMMAND)
		exec_simple_command(node->value);
}
