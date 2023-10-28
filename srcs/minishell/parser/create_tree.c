/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 05:20:23 by dlacuey           #+#    #+#             */
/*   Updated: 2023/10/28 09:55:34 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>
#include <stdbool.h>

static bool add_append(t_node **node, t_token token)
{
	(*node)->type = APPEND_REDIRECT;
	(*node)->right = init_node();
	if (!(*node)->right)
		return (false);
	(*node)->right->type = APPEND_REDIRECT;
	(*node)->right->head = (*node)->head;
	(*node)->right->parent = *node;
	if (!add_word((*node)->right, token.value))
		return (false);
	*node = (*node)->right;
	return (true);
}

#include <stdio.h>
static bool add_o_redirection(t_node **node, t_token token)
{
	(*node)->type = COMMAND_O_REDIRECT;
	(*node)->right = init_node();
	if (!(*node)->right)
		return (false);
	(*node)->right->type = COMMAND_O_REDIRECT;
	(*node)->right->head = (*node)->head;
	(*node)->right->parent = *node;
	if (!add_word((*node)->right, token.value))
		return (false);
	*node = (*node)->right;
	return (true);
}

static bool	add_i_redirection(t_node **node, t_token token)
{
	(*node)->type = COMMAND_I_REDIRECT;
	(*node)->right = init_node();
	if (!(*node)->right)
		return (false);
	(*node)->right->type = COMMAND_I_REDIRECT;
	(*node)->right->head = (*node)->head;
	(*node)->right->parent = *node;
	if (!add_word((*node)->right, token.value))
		return (false);
	*node = (*node)->right;
	return (true);
}

static bool	add_here_doc(t_node **node, t_token token)
{
	(*node)->type = HERE_DOCUMENT;
	(*node)->right = init_node();
	if (!(*node)->right)
		return (false);
	(*node)->right->type = HERE_DOCUMENT;
	(*node)->right->head = (*node)->head;
	(*node)->right->parent = *node;
	if (!add_word((*node)->right, token.value))
		return (false);
	*node = (*node)->right;
	return (true);
}

static void	is_simple_command(t_node *node, t_node *simple_command)
{
	if (node == node->head)
	{
		node->vector_strs.values = simple_command->vector_strs.values;
		free(simple_command);
	}
	else
	{
		node->parent->left = simple_command;
		simple_command->parent = node->parent;
	}
}

static bool	init_simple_command(t_node **simple_command, t_node *head)
{
	*simple_command = init_node();
	if (!*simple_command)
		return (false);
	(*simple_command)->type = SIMPLE_COMMAND;
	(*simple_command)->head = head;
	(*simple_command)->parent = NULL;
	(*simple_command)->left = NULL;
	(*simple_command)->right = NULL;
	return (true);
}

void	create_parser_map(t_parser_map parser_map[NUMBER_OF_TOKEN_TYPES])
{
	parser_map[O_REDIRECTION].function = add_o_redirection;
	parser_map[I_REDIRECTION].function = add_i_redirection;
	parser_map[APPEND_REDIRECTION].function = add_append;
	parser_map[HERE_DOC].function = add_here_doc;
}


static bool	create_nodes(t_parser_env env, t_token *tokens, size_t *index)
{
	e_token_type	type;

	type = tokens[*index].type;
	if (type == WORD)
	{
		if (!add_word(env.simple_command, tokens[*index].value))
			return (false);
	}
	else
	{
		if (!env.parser_map[type].function(env.head, tokens[++(*index)]))
			return (false);
	}
	return (true);
}

static bool	init_parser_env(t_parser_env *env, t_node **head)
{
	create_parser_map(env->parser_map);
	if (!init_simple_command(&env->simple_command, *head))
		return (false);
	env->head = head;
	return (true);
}

bool	create_tree(t_node *head, t_token_list *token_list)
{
	t_parser_env	env;
	size_t			index;

	index = 0;
	if (!init_parser_env(&env, &head))
		return (false);
	while (index < token_list->size)
	{
		if (!create_nodes(env, token_list->tokens, &index))
			return (false);
		index++;
	}
	is_simple_command(head, env.simple_command);
	return (true);
}
