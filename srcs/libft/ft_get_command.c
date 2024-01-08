/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:52:08 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/08 11:02:51 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include "../../includes/colors.h"

extern int exit_status;

void message_command_not_found(char *command)
{
	int stdout_fd;

	stdout_fd = dup(STDOUT_FILENO);
	if (dup2(2, STDOUT_FILENO) < 0)
	{
		(perror(RED"Dup2 failed"WHITE));
		return ;
	}
	printf(RED"-Wesh: %s: command not found\n"WHITE, command);
	if (dup2(stdout_fd, STDOUT_FILENO) < 0)
	{
		(perror(RED"Dup2 failed"WHITE));
		return ;
	}
	exit_status = 127;
}

bool	check_command(char *command)
{
	if (command[ft_strlen(command) - 1] == '/')
	{
		printf(RED"-Wesh: %s: Can't exec directory\n"WHITE, command);
		exit_status = 126;
		return (false);
	}
	else if (command[0] == '.' && command[1] == '\0')
	{
		printf(RED"-Wesh: %s: command not found\n"WHITE, command);
		exit_status = 2;
		return (false);
	}
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
