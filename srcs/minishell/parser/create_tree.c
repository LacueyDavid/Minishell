/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 05:20:23 by dlacuey           #+#    #+#             */
/*   Updated: 2023/10/26 11:11:13 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>
#include <stdbool.h>

bool	create_tree(t_node *node, t_token_list *token_list)
{
	t_node			*simple_command;
	t_node			*current_o_redirection;
	t_node			*last_current_o_redirection;
	size_t			index;

	node->head = node;
	node->type = O_REDIRECTION;
	simple_command = init_node();
	simple_command->head = node;
	if (!simple_command)
		return (false);
	simple_command->type = SIMPLE_COMMAND;
	current_o_redirection = node;
	index = 0;
	while (index < token_list->size)
	{
		if (token_list->tokens[index].type == WORD)
		{
			if (!add_word(simple_command, token_list->tokens[index].value))
				return (false);
		}
		else if (token_list->tokens[index].type == O_REDIRECTION)
		{
			index++;
			current_o_redirection->right = init_node();
			if (!current_o_redirection->right)
				return (false);
			current_o_redirection->right->type = O_REDIRECTION;
			if (!add_word(current_o_redirection->right, token_list->tokens[index].value))
				return (false);
			last_current_o_redirection = current_o_redirection;
			current_o_redirection = current_o_redirection->right;
			current_o_redirection->head = node;
		}
		index++;
	}
	current_o_redirection->type = SIMPLE_COMMAND;
	if (node == current_o_redirection)
	{
		node->vector_strs.values = simple_command->vector_strs.values;
		free(simple_command);
	}
	else
		last_current_o_redirection->left = simple_command;
	return (true);
}
