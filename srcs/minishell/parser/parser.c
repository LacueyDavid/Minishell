/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 05:18:08 by dlacuey           #+#    #+#             */
/*   Updated: 2023/10/26 15:31:19 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>

t_node	*parser(t_token_list *token_list)
{
	t_node	*node;

	node = init_node();
	if (!node)
		return (NULL);
	if (!create_tree(node, token_list))
	{
		clear_tree(node);
		return (NULL);
	}
	return (node);
}
