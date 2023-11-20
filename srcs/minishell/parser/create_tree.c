/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 05:20:23 by dlacuey           #+#    #+#             */
/*   Updated: 2023/11/17 18:43:41 by marvin           ###   ########.fr       */
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

bool	create_tree(t_parser_env *env, t_token_list *token_list)
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

static void	init_pipe_head(t_parser_env *env)
{
	env->head = init_node();
	env->head->type = COMMAND_PIPE;
	env->head->head = env->head;
	env->head->parent = env->head;
	env->head->left = NULL;
	env->head->right = NULL;
}

bool	create_piped_tree(t_parser_env *env, t_token_list *token_list)
{
	size_t			index;
	t_token_list	*tmp;
	t_parser_env	*tmp_env;

	index = 0;
	init_pipe_head(env);
	while (index < token_list->size)
	{
		tmp = pipeless_token_list(token_list, &index);
		tmp_env = env;
		if (!create_tree(tmp_env, tmp))
			return (false);
		if (index < token_list->size)
		{
			env->temporary->left = tmp_env->head;
			add_pipe(env);
		}
		else
			env->temporary->right = tmp_env->head;
		index++;
	}
	return (true);
}
