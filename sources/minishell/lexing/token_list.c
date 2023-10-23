/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 21:12:18 by dlacuey           #+#    #+#             */
/*   Updated: 2023/10/24 01:10:07 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include <stdlib.h>

void destroy_token_list(t_token_list *token_list)
{
	size_t index;

	index = 0;
	while (index < token_list->size)
	{
		free(token_list->tokens[index].value);
		index++;
	}
	free(token_list->tokens);
	free(token_list);
}

static void resize_token_list(t_token_list *token_list)
{
	size_t	old_size;
	size_t	new_size;
	void *test_realloc;
	old_size = token_list->capacity * sizeof(t_token);
	if (token_list->capacity == 0)
		token_list->capacity = 1;
	else
		token_list->capacity *= 2;
	new_size = token_list->capacity * sizeof(t_token);
	test_realloc = ft_realloc(token_list->tokens, new_size, old_size);
	if (!test_realloc)
		exit(1);
	token_list->tokens = test_realloc;
}

void add_token(t_token_list *token_list, t_token token)
{
	if (token_list->size == token_list->capacity)
		resize_token_list(token_list);
	token_list->tokens[token_list->size++] = token;
}

t_token_list *init_token_list(void)
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
