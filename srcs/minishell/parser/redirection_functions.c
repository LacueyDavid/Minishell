/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 10:17:51 by dlacuey           #+#    #+#             */
/*   Updated: 2023/11/15 05:44:41 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>
#include <stdbool.h>

static bool add_append(t_parser_env *env, t_token token)
{
	t_node *node;
	
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

static bool add_o_redirection(t_parser_env *env, t_token token)
{
	t_node *node;
	
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

static bool	add_i_redirection(t_parser_env *env, t_token token)
{
	t_node *node;
	
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

static bool	add_here_doc(t_parser_env *env, t_token token)
{
	t_node *node;
	
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

static bool	add_pipe(t_parser_env *env, t_token token)
{
	t_node *node;

	(void)token;
	env->number_of_pipes++;
	node = init_node();
	if (!node)
		return (false);
	node->type = COMMAND_PIPE;
	env->head->parent = node;
	node->left = env->head;
	env->head = node;
	node->right = NULL;
	return (true);
}

void	create_parser_map(t_parser_map parser_map[NUMBER_OF_TOKEN_TYPES])
{
	parser_map[O_REDIRECTION].function = add_o_redirection;
	parser_map[I_REDIRECTION].function = add_i_redirection;
	parser_map[APPEND_REDIRECTION].function = add_append;
	parser_map[HERE_DOC].function = add_here_doc;
	parser_map[PIPE].function = add_pipe;
}
