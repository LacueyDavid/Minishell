/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 05:20:23 by dlacuey           #+#    #+#             */
/*   Updated: 2023/11/20 16:24:33 by dlacuey          ###   ########.fr       */
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

static bool	create_nodes(t_parser_env *env, t_token *tokens, size_t *index)
{
	e_token_type	type;

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

t_token_list	*pipeless_token_list(t_token_list *token_list, size_t *index)
{
	t_token_list	*tmp;
	size_t			i;

	i = *index;
	tmp = init_token_list();
	while (i < token_list->size && token_list->tokens[i].type != PIPE)
	{
		add_token(tmp, token_list->tokens[i]);
		i++;
	}
	*index = i;
	return (tmp);
}

bool	add_pipe(t_parser_env *env)
{
	t_node *node;

	env->number_of_pipes++;
	node = init_node();
	if (!node)
		return (false);
	node->type = COMMAND_PIPE;
	env->temporary->right = node;
	node->head = env->temporary->head;
	node->parent = env->temporary;
	env->temporary = node;
	return (true);
}

bool	is_pipes(t_token *tokens, size_t size)
{
	size_t	index;

	index = 0;
	while (index < size)
	{
		if (tokens[index].type == PIPE)
			return (true);
		index++;
	}
	return (false);
}

bool	copy_tree(t_node *node, t_node *tmp_node)
{
	if (node->left)
	{
		tmp_node->left = init_node();
		if (!tmp_node->left)
			return (false);
		tmp_node->left->parent = tmp_node;
		if (!copy_tree(node->left, tmp_node->left))
			return (false);
	}
	if (node->right)
	{
		tmp_node->right = init_node();
		if (!tmp_node->right)
			return (false);
		tmp_node->right->parent = tmp_node;
		if (!copy_tree(node->right, tmp_node->right))
			return (false);
	}
	tmp_node->type = node->type;
	tmp_node->vector_strs = node->vector_strs;
	return (true);
}

bool	copy_env(t_parser_env *env, t_parser_env tmp_env)
{
	if(!init_parser_env(&tmp_env))
		return (false);
	tmp_env.head = init_node();
	if (!tmp_env.head)
		return (false);
	tmp_env.temporary = tmp_env.head;
	if(!copy_tree(env->head, tmp_env.head))
		return (false);
	return (true);
}

bool	create_piped_tree(t_parser_env *env, t_token_list *token_list)
{
	size_t			index;
	t_token_list	*tmp;
	t_parser_env	tmp_env;

	index = 0;
	if(!copy_env(env, tmp_env))
		return (false);
	if (is_pipes(token_list->tokens, token_list->size))
	{
		while (index < token_list->size)
		{
			tmp = pipeless_token_list(token_list, &index);
			if (!create_redirection_tree(&tmp_env, tmp))
				return (false);
			if (index < token_list->size)
			{
				env->temporary->left = tmp_env.head;
				add_pipe(env);
			}
			else
				env->temporary->right = tmp_env.head;
			index++;
			destroy_token_list(tmp);
			clear_tree(tmp_env.head);
		}
	}
	else
	{
		if (!create_redirection_tree(env, token_list))
			return (false);
	}
	return (true);
}
