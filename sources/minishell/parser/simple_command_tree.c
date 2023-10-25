/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command_tree.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 06:29:53 by dlacuey           #+#    #+#             */
/*   Updated: 2023/10/25 02:14:40 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdbool.h>
#include <stdlib.h>

bool	create_simple_command_tree(t_node *node, t_token_list *token_list)
{
	size_t index;

	index = 0;
	while (index < token_list->size)
	{
		if (token_list->tokens[index].type == WORD)
			if (!add_word(node, token_list->tokens[index].value))
				return (false);
		if (!node)
			return (false);
		index++;
	}
	node->type = SIMPLE_COMMAND;
	return (true);
}
