/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:53:01 by dlacuey           #+#    #+#             */
/*   Updated: 2023/09/09 23:49:29 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "libft.h"

extern char	**environ;

void	exec_command(char *input)
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
