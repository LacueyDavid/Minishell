/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 20:23:51 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/22 10:51:38 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdbool.h>
# include <stdlib.h>

# ifndef MINISHELL_IFS
#  define MINISHELL_IFS " \t\n\r\v\f\0"
# endif

# ifndef NUM_OF_TOKEN_TYPES
#  define NUM_OF_TOKEN_TYPES 6
# endif

typedef enum t_token_type
{
	WORD,
	O_REDIRECTION,
	I_REDIRECTION,
	APPEND_REDIRECTION,
	HERE_DOC,
	PIPE,
}					t_token_type;

typedef struct token
{
	char			*value;
	t_token_type	type;
}					t_token;

typedef struct token_list
{
	size_t			size;
	size_t			capacity;
	t_token			*tokens;
}					t_token_list;

t_token_list		*init_token_list(void);
t_token_list		*lexer(char *input);
bool				add_token(t_token_list *token_list, t_token token);
bool				tokenize_splited_input(t_token_list *token_list,
						char **splited_input);
bool				resize_token_list(t_token_list *token_list);
void				destroy_token_list(t_token_list *token_list);
size_t				ft_specialstrlen(char *input);
char				*put_space_between_special_chars(char *input);
void				update_quotes(char *input, bool *single_quotes,
						bool *double_quotes, size_t i);

#endif
