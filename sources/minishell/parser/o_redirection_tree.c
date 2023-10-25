/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_redirection_tree.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 06:29:37 by dlacuey           #+#    #+#             */
/*   Updated: 2023/10/25 07:55:04 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdbool.h>

// static bool	fill_nodes_o_redirection(t_node *left, t_node *right, t_token_list *token_list)
// {
// 	size_t			index;
//
// 	index = 0;
// 	while (index < token_list->size)
// 	{
// 		if (token_list->tokens[index].type == WORD)
// 		{
// 			if (!add_word(left, token_list->tokens[index].value))
// 				return (false);
// 		}
// 		else if (token_list->tokens[index].type == O_REDIRECTION)
// 		{
// 			index++;
// 			if (!add_word(right, token_list->tokens[index].value))
// 				return (false);
// 		}
// 		index++;
// 	}
// 	left->type = SIMPLE_COMMAND;
// 	right->type = SIMPLE_COMMAND;
// 	return (true);
// }

bool	create_o_redirection_tree(t_node *node, t_token_list *token_list)
{
	t_node			*simple_command;
	t_node			*current_o_redirection;
	size_t			index;


	node->type = O_REDIRECTION;
	simple_command = init_node();
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
			current_o_redirection->right->type = O_REDIRECTION;
			if (!add_word(current_o_redirection->right, token_list->tokens[index].value))
				return (false);
			current_o_redirection = current_o_redirection->right;
		}
		index++;
	}
	current_o_redirection->left = simple_command;
	return (true);





	// t_node			*left;
	// t_node			*right;
	//
	// if (!init_nodes(&left, &right))
	// 	return (false);
	// if (!fill_nodes_o_redirection(left, right, token_list))
	// 	return (false);
	// node->type = O_REDIRECTION;
	// node->left = left;
	// node->right = right;
	// return (true);
}
