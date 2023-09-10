/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 20:32:20 by dlacuey           #+#    #+#             */
/*   Updated: 2023/09/10 21:16:21 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer.h"
#include "libft.h"

t_token_list *lexer(char *input)
{
	t_token_list *token_list;
	t_token token;

	token_list = create_token_list();
	if (!token_list)
		return (NULL);
	token.type = WORD;
	token.value = ft_strdup(input);
	if (!token.value)
	{
		free(token_list);
		return (NULL);
	}
	add_token(token_list, token);
	token_list->size = 1;
	return (token_list);
}
