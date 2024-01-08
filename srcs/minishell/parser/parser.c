/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 05:18:08 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/08 16:31:40 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>
#include <stdio.h>

void	print_which_token(int type)
{
	if (type == PIPE)
		printf("wesh: syntax error near unexpected token `|'\n");
	else if (type == O_REDIRECTION)
		printf("wesh: syntax error near unexpected token `>'\n");
	else if (type == I_REDIRECTION)
		printf("wesh: syntax error near unexpected token `<'\n");
	else if (type == APPEND_REDIRECTION)
		printf("wesh: syntax error near unexpected token `>>'\n");
	else if (type == HERE_DOC)
		printf("wesh: syntax error near unexpected token `<<'\n");
	else
		printf("wesh: syntax error near unexpected token `newline'\n");
}

bool check_token_list(t_token_list *token_list)
{
	size_t i;

	i = 0;
	while (i < token_list->size)
	{
		if (token_list->tokens[i].type == O_REDIRECTION)
			if (token_list->tokens[i + 1].type != WORD)
			{
				print_which_token(token_list->tokens[i + 1].type);
				return (false);
			}
		if (token_list->tokens[i].type == I_REDIRECTION)
			if (token_list->tokens[i + 1].type != WORD)
			{
				print_which_token(token_list->tokens[i + 1].type);
				return (false);
			}
		if (token_list->tokens[i].type == APPEND_REDIRECTION)
			if (token_list->tokens[i + 1].type != WORD)
			{
				print_which_token(token_list->tokens[i + 1].type);
				return (false);
			}
		if (token_list->tokens[i].type == HERE_DOC)
			if (token_list->tokens[i + 1].type != WORD)
			{
				print_which_token(token_list->tokens[i + 1].type);
				return (false);
			}
		if (token_list->tokens[i].type == PIPE)
			if (i + 1 >= token_list->size || i == 0)
			{
				printf("wesh: syntax error near unexpected token `|'\n");
				return (false);
			}
		i++;
	}
	return (true);
}

t_node	*parser(t_token_list *token_list)
{
	t_parser_env	env;

	if (!check_token_list(token_list))
	{
		return (NULL);
	}
	if (!init_parser_env(&env))
		return (NULL);
	if (!create_piped_tree(&env, token_list))
	{
		clear_tree(env.head);
		return (NULL);
	}
	return (env.head);
}
