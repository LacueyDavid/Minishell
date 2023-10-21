/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:53:01 by dlacuey           #+#    #+#             */
/*   Updated: 2023/10/21 06:29:22 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "execution.h"
#include "fcntl.h"

extern char	**environ;

void	exec_simple_command(char **values)
{
	char	**paths;
	char	*command;

	paths = find_paths(environ);
	command = get_command(values[0], paths);
	execve(command, values, environ);
}

void	redirection_output(t_node *node)
{
	int	fd;

	fd = open(node->right->values[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
		exec_simple_command(node->values);
}

void	execution(t_node *tree)
{
		pid1 = fork();
		if (pid1 == 0)
			exec_full_command(tree);
		waitpid(pid1, NULL, 0);
}
