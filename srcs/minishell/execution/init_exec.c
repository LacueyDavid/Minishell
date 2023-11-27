/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 09:19:37 by dlacuey           #+#    #+#             */
/*   Updated: 2023/11/25 01:34:12 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "fcntl.h"
#include <unistd.h>

void	init_exec_func_map(t_exec_map exec_map[NUMBER_OF_EXEC_FUNCS])
{
	exec_map[SIMPLE_COMMAND].function = exec_simple_command;
	exec_map[COMMAND_O_REDIRECT].function = redirection_output;
	exec_map[COMMAND_I_REDIRECT].function = redirection_input;
	exec_map[APPEND_REDIRECT].function = append_output;
	exec_map[HERE_DOCUMENT].function = here_doc;
	// exec_map[PIPE].function = exec_pipes;
}

void	init_fds(int fds[NUMBER_OF_FDS])
{
	fds[1] = dup(1);
	fds[0] = dup(0);
}

void	close_fds(int fds[NUMBER_OF_FDS])
{
	close(fds[1]);
	close(fds[0]);
}

void	reset_standard_streams(int fds[NUMBER_OF_FDS])
{
	dup2(fds[0], STDIN_FILENO);
	dup2(fds[1], STDOUT_FILENO);
}
