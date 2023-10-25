/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 05:20:23 by dlacuey           #+#    #+#             */
/*   Updated: 2023/10/25 02:20:39 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>
#include <stdbool.h>

bool	create_tree(t_node *node, t_token_list *token_list)
{
	size_t	index;
	size_t	size;

	index = 0;
	size = token_list->size;
	while (index < size)
	{
		while (index < size && token_list->tokens[index].type == WORD)
			index++;
		if (index < size && token_list->tokens[index].type == O_REDIRECTION)
			return (create_o_redirection_tree(node, token_list));
	}
	return (create_simple_command_tree(node, token_list));
}
