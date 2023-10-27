/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 05:20:23 by dlacuey           #+#    #+#             */
/*   Updated: 2023/10/27 07:11:50 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>
#include <stdbool.h>

static bool	init_simple_command(t_node **simple_command, t_node *head)
{
	*simple_command = init_node();
	if (!*simple_command)
		return (false);
	(*simple_command)->head = head;
	(*simple_command)->type = SIMPLE_COMMAND;
	return (true);
}

static bool add_append(t_node **current, t_node **last_current, t_token token)
{
	(*current)->type = APPEND_REDIRECT;
	(*current)->right = init_node();
	if (!(*current)->right)
		return (false);
	(*current)->right->type = APPEND_REDIRECT;
	if (!add_word((*current)->right, token.value))
		return (false);
	*last_current = *current;
	*current = (*current)->right;
	return (true);
}

static void	init_current_redirection(t_node **current, t_node **head)
{
	(*head)->head = *head;
	(*head)->type = SIMPLE_COMMAND;
	*current = *head;
}

static bool add_o_redirection(t_node **current, t_node **last_current, t_token token)
{
	(*current)->type = COMMAND_O_REDIRECT;
	(*current)->right = init_node();
	if (!(*current)->right)
		return (false);
	(*current)->right->type = COMMAND_O_REDIRECT;
	if (!add_word((*current)->right, token.value))
		return (false);
	*last_current = *current;
	*current = (*current)->right;
	return (true);
}

static bool	add_i_redirection(t_node **current, t_node **last_current, t_token token)
{
	(*current)->type = COMMAND_I_REDIRECT;
	(*current)->right = init_node();
	if (!(*current)->right)
		return (false);
	(*current)->right->type = COMMAND_I_REDIRECT;
	if (!add_word((*current)->right, token.value))
		return (false);
	*last_current = *current;
	*current = (*current)->right;
	return (true);
}

static void	is_simple_command(t_node *head, t_node *simple_command, t_node *current_redirection, t_node *last_redirection)
{
	if (head == current_redirection)
	{
		head->vector_strs.values = simple_command->vector_strs.values;
		free(simple_command);
	}
	else
		last_redirection->left = simple_command;
}

bool	create_tree(t_node *head, t_token_list *token_list)
{
	t_node			*simple_command;
	t_node			*current_redirection;
	t_node			*last_redirection;
	size_t			index;

	index = 0;
	
	init_current_redirection(&current_redirection, &head);
	if (!init_simple_command(&simple_command, head))
		return (false);
	while (index < token_list->size)
	{
		if (token_list->tokens[index].type == WORD)
			if (!add_word(simple_command, token_list->tokens[index].value))
				return (false);
		if (token_list->tokens[index].type == O_REDIRECTION)
		{
			index++;
			if (!add_o_redirection(&current_redirection, &last_redirection, token_list->tokens[index]))
				return (false);
		}
		if (token_list->tokens[index].type == I_REDIRECTION)
		{
			index++;
			if (!add_i_redirection(&current_redirection, &last_redirection, token_list->tokens[index]))
				return (false);
		}
		if (token_list->tokens[index].type == APPEND_REDIRECTION)
		{
			index++;
			if (!add_append(&current_redirection, &last_redirection, token_list->tokens[index]))
				return (false);
		}
		index++;
	}
	is_simple_command(head, simple_command, current_redirection, last_redirection);
	return (true);
}
