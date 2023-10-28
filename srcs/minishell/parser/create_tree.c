/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 05:20:23 by dlacuey           #+#    #+#             */
/*   Updated: 2023/10/28 10:20:23 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>
#include <stdbool.h>

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
