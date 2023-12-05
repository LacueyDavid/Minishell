/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 08:07:24 by jdenis            #+#    #+#             */
/*   Updated: 2023/12/05 10:35:37 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "builtins.h"
#include <string.h>
#include "libft.h"

extern int	exit_status;

// bool	is_a_builtin(char *command)
// {
// 	if (!command)
// 		return (false);
// 	if (!ft_strcmp(command, "echo") || !ft_strcmp(command, "cd"))
// 		return (true);
// 	if (!ft_strcmp(command, "pwd") || !ft_strcmp(command, "export"))
// 		return (true);
// 	if (!ft_strcmp(command, "unset") || !ft_strcmp(command, "env"))
// 		return (true);
// 	if (!ft_strcmp(command, "exit"))
// 		return (true);
// 	return (false);
// }

bool	is_a_builtin(char *command)
{
	if (!command)
		return (false);
	if (!ft_strcmp(command, "echo"))
		return (true);
	if (!ft_strcmp(command, "cd"))
		return (true);
	if (!ft_strcmp(command, "pwd"))
		return (true);
	if (!ft_strcmp(command, "export"))
		return (true);
	if (!ft_strcmp(command, "unset"))
		return (true);
	if (!ft_strcmp(command, "env"))
		return (true);
	if (!ft_strcmp(command, "exit"))
		return (true);
	return (false);
}

char	*ft_compact_strs(char **strs)
{
	char	*string;
	size_t	size;
	size_t	index;

	index = 0;
	size = 0;
	while (strs[index])
	{
		size += ft_strlen(strs[index]);
		index++;
	}
	string = malloc(sizeof(char) * size + 1);
	if (!string)
		return (NULL);
	string[0] = '\0';
	index = 0;
	while (strs[index])
	{
		strcat(string, strs[index]); //utilise les ft
		strcat(string, " ");
		index++;
	}
	return (string);
}

int	exec_builtin(char **command)
{
	int		exit_status;
	char	*string_command;
	exit_status = EXIT_FAILURE;
	string_command = NULL;
	string_command = ft_compact_strs(command);
	if (!ft_strcmp(command[0], "echo"))
		exit_status = ft_echo(string_command);
	if (!ft_strcmp(command[0], "cd"))
		exit_status = ft_cd(string_command);
	if (!ft_strcmp(command[0], "pwd"))
		exit_status = ft_pwd();
	// if (!ft_strcmp(command[0], "export"))
	// 	exit_status = ft_export(string_command);
	// if (!ft_strcmp(command[0], "unset"))
	// 	exit_status = ft_unset(string_command);
	if (!ft_strcmp(command[0], "env"))
		exit_status = ft_env();
	if (!ft_strcmp(command[0], "exit"))
		exit_status = ft_exit(string_command);
	free(string_command);
	return (exit_status);
}