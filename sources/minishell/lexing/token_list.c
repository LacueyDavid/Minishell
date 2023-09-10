/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 21:12:18 by dlacuey           #+#    #+#             */
/*   Updated: 2023/09/10 21:18:16 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include <stdlib.h>

void destroy_token_list(t_token_list *token_list)
{
	free(token_list->tokens[0].value);
	free(token_list->tokens);
	free(token_list);
}

static void resize_token_list(t_token_list *token_list)
{
	void *test_realloc;
	if (token_list->capacity == 0)
		token_list->capacity = 1;
	else
		token_list->capacity *= 2;
	test_realloc = ft_realloc(token_list->tokens, token_list->capacity);
	if (!test_realloc)
	{
		exit(1);
	}
	token_list->tokens = test_realloc;
}

void add_token(t_token_list *token_list, t_token token)
{
	if (token_list->size == token_list->capacity)
		resize_token_list(token_list);
	token_list->tokens[token_list->size++] = token;
}

t_token_list *create_token_list(void)
{
	t_token_list *token_list;

	token_list = malloc(sizeof(t_token_list));
	if (!token_list)
		return (NULL);
	token_list->tokens = NULL;
	token_list->size = 0;
	token_list->capacity = 0;
	return (token_list);
}

