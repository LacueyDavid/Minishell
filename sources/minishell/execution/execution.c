/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:53:01 by dlacuey           #+#    #+#             */
/*   Updated: 2023/10/17 02:01:34 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "libft.h"
#include "execution.h"

extern char	**environ;

void	exec_simple_command(char *input)
{
	char	**argv;
	pid_t	pid1;
	char	**paths;
	char	*command;

	argv = ft_split(input, ' ');
	paths = find_paths(environ);
	command = get_command(argv[0], paths);
	pid1 = fork();
	if (pid1 == 0)
		execve(command, argv, environ);
	waitpid(pid1, NULL, 0);
}

void	exec_full_command(t_node *node)
{
	if (node->type == SIMPLE_COMMAND)
		exec_simple_command(node->value);
}
