/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 20:23:51 by dlacuey           #+#    #+#             */
/*   Updated: 2023/10/25 03:19:07 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include <stdlib.h>
#include <stdbool.h>

# ifndef MINISHELL_IFS
#  define MINISHELL_IFS " \t\n\r\v\f"
# endif

typedef enum e_token_type
{
	WORD,
	O_REDIRECTION,
	SIMPLE_COMMAND
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

t_token_list	*init_token_list(void);
t_token_list	*lexer(char *input);
void			destroy_token_list(t_token_list *token_list);
void			add_token(t_token_list *token_list, t_token token);
bool			tokenize_splited_input(t_token_list *token_list, char **splited_input);

#endif
