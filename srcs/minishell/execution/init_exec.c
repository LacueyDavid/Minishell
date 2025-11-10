/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 09:19:37 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/06 18:40:59 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "fcntl.h"
#include <unistd.h>

void	init_exec(t_exec *exec, t_envs *envs)
{
	exec->exec_map[COMMAND_O_REDIRECT].function = redirection_output;
	exec->exec_map[COMMAND_I_REDIRECT].function = redirection_input;
	exec->exec_map[APPEND_REDIRECT].function = append_output;
	exec->fds[0] = dup(STDIN_FILENO);
	exec->fds[1] = dup(STDOUT_FILENO);
	exec->envs = envs;
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
