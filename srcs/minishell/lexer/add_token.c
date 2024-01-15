/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 02:57:27 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/15 18:32:25 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include <stdlib.h>

bool	resize_token_list(t_token_list *token_list)
{
	size_t	old_size;
	size_t	new_size;
	void	*test_realloc;

	old_size = token_list->capacity * sizeof(t_token);
	if (token_list->capacity == 0)
		token_list->capacity = 1;
	else
		token_list->capacity *= 2;
	new_size = token_list->capacity * sizeof(t_token);
	test_realloc = ft_realloc(token_list->tokens, new_size, old_size);
	if (!test_realloc)
		return (false);
	token_list->tokens = test_realloc;
	return (true);
}

bool	add_token(t_token_list *token_list, t_token token)
{
	if (token_list->size == token_list->capacity)
		if (!resize_token_list(token_list))
			return (false);
	token_list->tokens[token_list->size++] = token;
	return (true);
}
