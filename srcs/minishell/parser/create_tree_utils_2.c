/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 20:59:21 by jdenis            #+#    #+#             */
/*   Updated: 2024/01/22 17:25:04 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

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

static bool	create_nodes(t_parser_env *env, t_token *tokens, size_t *index)
{
	t_token_type	type;

	type = tokens[*index].type;
	if (type != WORD)
		(*index)++;
	if (!env->parser_map[type].function(env, tokens[*index]))
		return (false);
	return (true);
}

bool	create_redirection_tree(t_parser_env *env, t_token_list *token_list)
{
	size_t	index;

	index = 0;
	while (index < token_list->size)
	{
		if (!create_nodes(env, token_list->tokens, &index))
			return (false);
		index++;
	}
	is_simple_command(env->temporary, env->simple_command);
	return (true);
}

bool	copy_token(t_token_list *token_list, t_token token)
{
	t_token	token_to_copy;

	token_to_copy.type = token.type;
	token_to_copy.value = ft_strdup(token.value);
	if (!token_to_copy.value)
		return (false);
	if (!add_token(token_list, token_to_copy))
		return (false);
	return (true);
}

bool	fill_tmp(t_token_list *token_list, t_token token)
{
	if (token_list->size == token_list->capacity)
	{
		if (!resize_token_list(token_list))
			return (false);
	}
	if (!token_list->tokens)
		return (false);
	copy_token(token_list, token);
	return (true);
}
