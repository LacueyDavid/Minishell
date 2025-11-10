/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 05:18:08 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/07 12:31:24 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

static bool	protect_newline(t_token_list *token_list, size_t i)
{
	if (i + 1 >= token_list->size)
	{
		print_which_token(42);
		return (false);
	}
	return (true);
}

static bool	protect_appends(t_token_list *token_list, size_t i)
{
	if (token_list->tokens[i].type == APPEND_REDIRECTION)
	{
		if (!protect_newline(token_list, i))
			return (false);
		if (token_list->tokens[i + 1].type != WORD)
		{
			print_which_token(token_list->tokens[i + 1].type);
			return (false);
		}
	}
	return (true);
}

static bool	protect_redirections(t_token_list *token_list, size_t i)
{
	if (!protect_appends(token_list, i))
		return (false);
	if (token_list->tokens[i].type == O_REDIRECTION)
	{
		if (!protect_newline(token_list, i))
			return (false);
		if (token_list->tokens[i + 1].type != WORD)
		{
			print_which_token(token_list->tokens[i + 1].type);
			return (false);
		}
	}
	if (token_list->tokens[i].type == I_REDIRECTION)
	{
		if (!protect_newline(token_list, i))
			return (false);
		if (token_list->tokens[i + 1].type != WORD)
		{
			print_which_token(token_list->tokens[i + 1].type);
			return (false);
		}
	}
	return (true);
}

static bool	protect_pipe_and_here_doc(t_token_list *token_list, size_t i)
{
	if (token_list->tokens[i].type == PIPE)
	{
		if (i + 1 >= token_list->size || i == 0)
		{
			printf("wesh: syntax error near unexpected token `|'\n");
			return (false);
		}
		else if (token_list->tokens[i + 1].type == PIPE)
		{
			printf("wesh: syntax error near unexpected token `|'\n");
			return (false);
		}
	}
	if (token_list->tokens[i].type == HERE_DOC)
	{
		if (!protect_newline(token_list, i))
			return (false);
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
		if (token_list->size == 1 && token_list->tokens[i].type != WORD)
		{
			print_which_token(token_list->tokens[0].type);
			return (false);
		}
		if (!protect_redirections(token_list, i))
			return (false);
		if (!protect_pipe_and_here_doc(token_list, i))
			return (false);
		i++;
	}
	return (true);
}
