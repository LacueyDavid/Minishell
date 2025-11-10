/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_piped_tree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:46:54 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/16 11:54:31 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool	reset_head(t_parser_env *env)
{
	env->head = init_node();
	if (!env->head)
		return (false);
	env->head->head = env->head;
	env->temporary = env->head;
	if (!init_simple_command(&env->simple_command, env->head))
		return (false);
	return (true);
}

static bool	add_pipe_node_to_tree(t_parser_env *env, t_parser_env *tmp_env)
{
	env->temporary->left = tmp_env->head;
	if (!reset_head(tmp_env))
		return (false);
	if (!add_pipe(env))
		return (false);
	return (true);
}

static bool	add_last_node_to_piped_tree(t_parser_env *env,
			t_parser_env *tmp_env, t_token_list *tmp2)
{
	env->temporary->left = tmp_env->head;
	if (!reset_head(tmp_env))
		return (false);
	if (!create_redirection_tree(tmp_env, tmp2))
		return (false);
	env->temporary->right = tmp_env->head;
	return (true);
}

bool	init_parser_env_piped_tree(t_tmp_envs *tmps, t_parser_env *env)
{
	tmps->index = 0;
	if (!init_parser_env(&tmps->tmp_env))
		return (false);
	if (!copy_env(env, &tmps->tmp_env))
		return (false);
	free(env->simple_command);
	env->temporary->type = COMMAND_PIPE;
	env->number_of_pipes++;
	return (true);
}

bool	add_nodes_to_piped_tree(t_parser_env *env, t_tmp_envs *tmps,
			t_token_list *token_list)
{
	if (tmps->index == 0)
		tmps->tmp1 = pipeless_token_list(token_list, &tmps->index);
	if (!tmps->tmp1)
		return (false);
	if (tmps->index < token_list->size)
		tmps->index++;
	tmps->tmp2 = pipeless_token_list(token_list, &tmps->index);
	if (!tmps->tmp2)
		return (false);
	if (!create_redirection_tree(&tmps->tmp_env, tmps->tmp1))
		return (false);
	if (tmps->index < token_list->size)
	{
		if (!add_pipe_node_to_tree(env, &tmps->tmp_env))
			return (false);
	}
	else
		if (!add_last_node_to_piped_tree(env, &tmps->tmp_env, tmps->tmp2))
			return (false);
	destroy_token_list(tmps->tmp1);
	tmps->tmp1 = tmps->tmp2;
	return (true);
}
