/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 10:17:51 by dlacuey           #+#    #+#             */
/*   Updated: 2023/10/28 10:19:24 by dlacuey          ###   ########.fr       */
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

void	create_parser_map(t_parser_map parser_map[NUMBER_OF_TOKEN_TYPES])
{
	parser_map[O_REDIRECTION].function = add_o_redirection;
	parser_map[I_REDIRECTION].function = add_i_redirection;
	parser_map[APPEND_REDIRECTION].function = add_append;
	parser_map[HERE_DOC].function = add_here_doc;
}
