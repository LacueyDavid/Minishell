/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:53:01 by dlacuey           #+#    #+#             */
/*   Updated: 2023/10/24 03:19:14 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "execution.h"
#include "fcntl.h"
#include <sys/wait.h>
#include <stdio.h>

extern char	**environ;

void	exec_simple_command(char **values)
{
	char	**paths;
	char	*command;

	paths = find_paths(environ);
	command = get_command(values[0], paths);
	execve(command, values, environ);
	(perror("Command not found"), exit(1));
}

void	redirection_output(t_node *node)
{
	int	fd;

	fd = open(node->right->values[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		(perror("Open failed"), exit(1));
	if (dup2(fd, 1) < 0)
		(perror("Dup2 failed"), exit(1));
	if (close(fd) < 0)
		(perror("Close failed"), exit(1));
}

void	exec_full_command(t_node *node)
{
	if (node->type == O_REDIRECTION)
	{
		redirection_output(node);
		exec_full_command(node->left);
	}
	else if (node->type == SIMPLE_COMMAND)
		exec_simple_command(node->values);
}

void	execution(t_node *tree)
{
	// refacto : fork dans exec_full_command
	// refacto : dup(1) plutot que fork comme jimmy avait voulu faire
	pid_t	pid1;

	pid1 = fork();
	if (pid1 < 0)
	{
		(perror("Fork failed"));
		return ;
	}
	else
		if (pid1 == 0)
			exec_full_command(tree);
	waitpid(pid1, NULL, 0);
}
