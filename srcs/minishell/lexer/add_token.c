/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 02:57:27 by dlacuey           #+#    #+#             */
/*   Updated: 2023/11/23 06:26:33 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "lexer.h"

void resize_token_list(t_token_list *token_list)
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

