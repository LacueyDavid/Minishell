/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 05:20:23 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/15 21:06:01 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool	reset_head(t_parser_env *env)
{
	env->head = init_node();
	if (!env->head)
		return (false);
	env->head->head = env->head;
	env->temporary = env->head;
	if (!init_simple_command(&env->simple_command, env->head))
		return (false);
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

bool	copy_env(const t_parser_env *env, t_parser_env *tmp_env_ptr)
{
	if (!copy_tree(env->head, tmp_env_ptr->head))
		return (false);
	tmp_env_ptr->number_of_pipes = env->number_of_pipes;
	return (true);
}

void	put_the_good_head(t_node *head, t_node *node)
{
	if (!node || !head)
		return ;
	put_the_good_head(head, node->left);
	put_the_good_head(head, node->right);
	node->head = head;
}

bool	create_piped_tree(t_parser_env *env, t_token_list *token_list)
{
	size_t			index;
	t_token_list	*tmp1;
	t_token_list	*tmp2;
	t_parser_env	tmp_env;

	index = 0;
	if (is_pipes(token_list->tokens, token_list->size))
	{
		if (!init_parser_env(&tmp_env))
			return (false);
		if (!copy_env(env, &tmp_env))
			return (false);
		free(env->simple_command);
		env->temporary->type = COMMAND_PIPE;
		env->number_of_pipes++;
		while (index < token_list->size)
		{
			if (index == 0)
				tmp1 = pipeless_token_list(token_list, &index);
			if (!tmp1)
				return (false);
			if (index < token_list->size)
				index++;
			tmp2 = pipeless_token_list(token_list, &index);
			if (!tmp2)
				return (false);
			if (!create_redirection_tree(&tmp_env, tmp1))
				return (false);
			if (index < token_list->size)
			{
				env->temporary->left = tmp_env.head;
				if (!reset_head(&tmp_env))
					return (false);
				if (!add_pipe(env))
					return (false);
			}
			else
			{
				env->temporary->left = tmp_env.head;
				if (!reset_head(&tmp_env))
					return (false);
				if (!create_redirection_tree(&tmp_env, tmp2))
					return (false);
				env->temporary->right = tmp_env.head;
			}
			destroy_token_list(tmp1);
			tmp1 = tmp2;
		}
		destroy_token_list(tmp1);
		env->head->number_of_pipes = env->number_of_pipes;
		put_the_good_head(env->head, env->head);
	}
	else
	{
		if (!create_redirection_tree(env, token_list))
			return (false);
	}
	return (true);
}
