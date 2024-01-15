/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 05:19:59 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/15 18:33:00 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdbool.h>
#include <stdlib.h>

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
	node->parent = NULL;
	node->number_of_pipes = 0;
	node->number_of_here_doc = 0;
	node->number_of_here_doc_index = 0;
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

bool	init_simple_command(t_node **simple_command, t_node *head)
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

bool	init_parser_env(t_parser_env *env)
{
	create_parser_map(env->parser_map);
	env->number_of_pipes = 0;
	env->head = init_node();
	if (!env->head)
		return (false);
	env->head->head = env->head;
	env->temporary = env->head;
	if (!init_simple_command(&env->simple_command, env->head))
		return (false);
	return (true);
}
