/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_protections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 04:34:03 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/08 06:57:29 by dlacuey          ###   ########.fr       */
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

bool	protect_redirection(t_node *node, t_exec *exec)
{
	if (!expand_env_variables(&(node->vector_strs), exec->envs))
		return (false);
	if (node->vector_strs.values)
		if (!node->vector_strs.values[0])
			return (perror(RED "wesh: ambiguous redirect" WHITE), false);
	return (true);
}

void	expand_fail_protection(t_node *node, t_exec *exec)
{
	if (!node->vector_strs.values)
	{
		g_exit_status = 1;
		perror(RED "Expand env variables failed" WHITE);
		clear_tree(node->head);
		if (exec)
		{
			free_envs(exec->envs);
			reset_standard_streams(exec->fds);
			close_fds(exec->fds);
		}
		exit(g_exit_status);
	}
}

void	wildcards_fail_protection(t_node *node, t_exec *exec)
{
	if (!node->vector_strs.values)
	{
		g_exit_status = 134;
		perror(RED "Wildcards failed"WHITE);
		clear_tree(node->head);
		if (exec)
		{
			free_envs(exec->envs);
			reset_standard_streams(exec->fds);
			close_fds(exec->fds);
		}
		exit(g_exit_status);
	}
}

void	vector_null_protection(t_node *node, t_exec *exec)
{
	(g_exit_status = 0);
	clear_tree(node->head);
	if (exec)
	{
		free_envs(exec->envs);
		reset_standard_streams(exec->fds);
		close_fds(exec->fds);
	}
	exit(g_exit_status);
}
