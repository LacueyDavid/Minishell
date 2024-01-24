/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 01:17:50 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/24 15:21:02 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "colors.h"
#include "environnement.h"
#include "execution.h"
#include "get_next_line.h"
#include "here_doc.h"
#include "libft.h"
#include "minishell_signals.h"
#include "wildcards.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

extern int	g_exit_status;

static void	message_command_not_found(char *command)
{
	int	stdout_fd;

	stdout_fd = dup(STDOUT_FILENO);
	if (dup2(2, STDOUT_FILENO) < 0)
	{
		(perror(RED "Dup2 failed" WHITE));
		return ;
	}
	printf(RED "%s: command not found\n" WHITE, command);
	if (dup2(stdout_fd, STDOUT_FILENO) < 0)
	{
		(perror(RED "Dup2 failed" WHITE));
		return ;
	}
	g_exit_status = 127;
}

static bool	check_if_its_a_directory(char *command)
{
	DIR	*dir;

	dir = opendir(command);
	if (dir != NULL)
	{
		printf(RED "-Wesh: %s: Can't exec directory\n" WHITE, command);
		g_exit_status = 126;
		closedir(dir);
		return (false);
	}
	closedir(dir);
	return (true);
}

static bool	check_command(char *command)
{
	if (command == NULL)
		return (false);
	if (command[0] == '\0')
	{
		printf(RED "Command '' not found\n" WHITE);
		g_exit_status = 127;
		return (false);
	}
	if (command[0] == '.' && command[1] == '\0')
	{
		printf(RED "%s: command not found\n" WHITE, command);
		g_exit_status = 2;
		return (false);
	}
	if (!check_if_its_a_directory(command))
		return (false);
	return (true);
}

char	*get_command(char *command, char **paths)
{
	char	*tmp;
	char	*command_full_path;

	if (!check_command(command))
		return (NULL);
	if (access(command, X_OK) == 0)
		return (command);
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command_full_path = ft_strjoin(tmp, command);
		free(tmp);
		if (access(command_full_path, X_OK) == 0)
			return (command_full_path);
		free(command_full_path);
		paths++;
	}
	message_command_not_found(command);
	return (NULL);
}
