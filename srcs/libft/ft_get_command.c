/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:52:08 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/06 15:00:46 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include "../../includes/colors.h"

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
}

char	*get_command(char *command, char **paths)
{
	char	*tmp;
	char	*command_full_path;

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
