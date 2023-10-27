/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 05:19:59 by dlacuey           #+#    #+#             */
/*   Updated: 2023/10/27 05:30:47 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>
#include <stdbool.h>

t_node	*init_node(void)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = 0;
	node->vector_strs.capacity = 0;
	node->vector_strs.size = 0;
	node->vector_strs.values = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

bool	init_nodes(t_node **left, t_node **right)
{
	*left = init_node();
	*right = init_node();
	if (!*left || !*right)
		return (false);
	return (true);
}
