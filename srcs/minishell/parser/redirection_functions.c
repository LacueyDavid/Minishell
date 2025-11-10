/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 10:17:51 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/15 21:09:48 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool	add_simple_command(t_parser_env *env, t_token token)
{
	if (!add_word(env->simple_command, token.value))
		return (false);
	return (true);
}

bool	add_append(t_parser_env *env, t_token token)
{
	t_node	*node;

	node = env->temporary;
	node->type = APPEND_REDIRECT;
	node->right = init_node();
	if (!node->right)
		return (false);
	node->right->type = APPEND_REDIRECT;
	node->right->head = node->head;
	node->right->parent = node;
	if (!add_word(node->right, token.value))
		return (false);
	env->temporary = node->right;
	return (true);
}

bool	add_o_redirection(t_parser_env *env, t_token token)
{
	t_node	*node;

	node = env->temporary;
	node->type = COMMAND_O_REDIRECT;
	node->right = init_node();
	if (!node->right)
		return (false);
	node->right->type = COMMAND_O_REDIRECT;
	node->right->head = node->head;
	node->right->parent = node;
	if (!add_word(node->right, token.value))
		return (false);
	env->temporary = node->right;
	return (true);
}

bool	add_i_redirection(t_parser_env *env, t_token token)
{
	t_node	*node;

	node = env->temporary;
	node->type = COMMAND_I_REDIRECT;
	node->right = init_node();
	if (!node->right)
		return (false);
	node->right->type = COMMAND_I_REDIRECT;
	node->right->head = node->head;
	node->right->parent = node;
	if (!add_word(node->right, token.value))
		return (false);
	env->temporary = node->right;
	return (true);
}

bool	add_here_doc(t_parser_env *env, t_token token)
{
	t_node	*node;

	node = env->temporary;
	node->type = HERE_DOCUMENT;
	node->right = init_node();
	if (!node->right)
		return (false);
	node->right->type = HERE_DOCUMENT;
	node->right->head = node->head;
	node->right->parent = node;
	if (!add_word(node->right, token.value))
		return (false);
	env->temporary = node->right;
	return (true);
}
