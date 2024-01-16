/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 05:18:08 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/16 11:16:00 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

extern int	g_exit_status;

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

bool	protect_redirections(t_token_list *token_list, size_t i)
{
	if (token_list->tokens[i].type == O_REDIRECTION)
	{
		if (token_list->tokens[i + 1].type != WORD)
		{
			print_which_token(token_list->tokens[i + 1].type);
			return (false);
		}
	}
	if (token_list->tokens[i].type == I_REDIRECTION)
	{
		if (token_list->tokens[i + 1].type != WORD)
		{
			print_which_token(token_list->tokens[i + 1].type);
			return (false);
		}
	}
	if (token_list->tokens[i].type == APPEND_REDIRECTION)
	{
		if (token_list->tokens[i + 1].type != WORD)
		{
			print_which_token(token_list->tokens[i + 1].type);
			return (false);
		}
	}
	return (true);
}

bool	protect_pipe_and_here_doc(t_token_list *token_list, size_t i)
{
	if (token_list->tokens[i].type == PIPE)
	{
		if (i + 1 >= token_list->size || i == 0)
		{
			printf("wesh: syntax error near unexpected token `|'\n");
			return (false);
		}
	}
	if (token_list->tokens[i].type == HERE_DOC)
	{
		if (token_list->tokens[i + 1].type != WORD)
		{
			print_which_token(token_list->tokens[i + 1].type);
			return (false);
		}
	}
	return (true);
}

bool	check_token_list(t_token_list *token_list)
{
	size_t	i;

	i = 0;
	while (i < token_list->size)
	{
		if (!protect_redirections(token_list, i))
			return (false);
		if (!protect_pipe_and_here_doc(token_list, i))
			return (false);
		i++;
	}
	return (true);
}

t_node	*parser(t_token_list *token_list)
{
	t_parser_env	env;

	if (!check_token_list(token_list))
	{
		g_exit_status = 2;
		return (NULL);
	}
	if (!init_parser_env(&env))
		return (NULL);
	if (!create_full_tree(&env, token_list))
	{
		clear_tree(env.head);
		return (NULL);
	}
	return (env.head);
}
