/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 20:23:51 by dlacuey           #+#    #+#             */
/*   Updated: 2023/09/10 21:19:18 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include <stddef.h>

typedef enum e_token_type
{
	WORD
}   e_token_type;

typedef struct token
{
	char			*value;
	e_token_type	type;
}	t_token;

typedef struct token_list
{
	size_t	size;
	size_t	capacity;
	t_token	*tokens;
}	t_token_list;

void destroy_token_list(t_token_list *token_list);
void add_token(t_token_list *token_list, t_token token);
t_token_list *create_token_list(void);
t_token_list *lexer(char *input);

#endif
