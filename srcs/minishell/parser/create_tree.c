/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 05:20:23 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/25 14:46:03 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool	is_pipes(t_token *tokens, size_t size)
{
	size_t	index;

	index = 0;
	while (index < size)
	{
		if (tokens[index].type == PIPE)
			return (true);
		index++;
	}
	return (false);
}

bool	copy_env(const t_parser_env *env, t_parser_env *tmp_env_ptr)
{
	if (!copy_tree(env->head, tmp_env_ptr->head))
		return (false);
	tmp_env_ptr->number_of_pipes = env->number_of_pipes;
	return (true);
}

static void	put_the_good_head(t_node *head, t_node *node)
{
	if (!node || !head)
		return ;
	put_the_good_head(head, node->left);
	put_the_good_head(head, node->right);
	node->head = head;
}

bool	create_piped_tree(t_parser_env *env, t_token_list *token_list)
{
	t_tmp_envs	tmps;

	if (!init_parser_env_piped_tree(&tmps, env))
		return (false);
	while (tmps.index < token_list->size)
		if (!add_nodes_to_piped_tree(env, &tmps, token_list))
			return (false);
	destroy_token_list(tmps.tmp1);
	env->head->number_of_pipes = env->number_of_pipes;
	put_the_good_head(env->head, env->head);
	return (true);
}

bool	create_full_tree(t_parser_env *env, t_token_list *token_list)
{
	if (is_pipes(token_list->tokens, token_list->size))
	{
		if (!create_piped_tree(env, token_list))
			return (false);
	}
	else
		if (!create_redirection_tree(env, token_list))
			return (false);
	return (true);
}
