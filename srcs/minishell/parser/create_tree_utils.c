/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 20:58:42 by jdenis            #+#    #+#             */
/*   Updated: 2024/01/15 21:52:55 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

t_token_list	*pipeless_token_list(t_token_list *token_list, size_t *index)
{
	t_token_list	*tmp;
	size_t			i;

	i = *index;
	tmp = init_token_list();
	if (!tmp)
		return (NULL);
	while (i < token_list->size && token_list->tokens[i].type != PIPE)
	{
		if (!copy_token(tmp, token_list->tokens[i]))
		{
			destroy_token_list(tmp);
			return (NULL);
		}
		i++;
	}
	*index = i;
	return (tmp);
}

bool	add_pipe(t_parser_env *env)
{
	t_node	*node;

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

bool	add_last_command(t_parser_env *env)
{
	t_node	*node;

	node = init_node();
	if (!node)
		return (false);
	node->type = SIMPLE_COMMAND;
	env->temporary->right = node;
	node->head = env->temporary->head;
	node->parent = env->temporary;
	env->temporary = node;
	return (true);
}

t_vector_strs	copy_vector_strs(t_vector_strs vector_strs)
{
	t_vector_strs	tmp;
	size_t			index;

	index = 0;
	tmp.size = vector_strs.size;
	tmp.capacity = vector_strs.capacity;
	tmp.values = (char **)malloc(sizeof(char *) * (tmp.capacity + 1));
	if (!tmp.values)
		return ((t_vector_strs){0});
	while (index < tmp.size && vector_strs.values[index])
	{
		tmp.values[index] = ft_strdup(vector_strs.values[index]);
		if (!tmp.values[index])
		{
			free_strs(tmp.values);
			return ((t_vector_strs){0});
		}
		index++;
	}
	tmp.values[index] = NULL;
	return (tmp);
}
