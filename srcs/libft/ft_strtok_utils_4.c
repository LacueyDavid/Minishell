/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_utils_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:48:24 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/16 10:56:31 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include "../../includes/colors.h"

static char	**init_tokens(char *str_to_tokenize, char *separators)
{
	char	**tokens;
	ssize_t	tokens_counted;

	if (!str_to_tokenize || !separators)
		return (NULL);
	tokens_counted = count_tokens(str_to_tokenize, separators);
	if (tokens_counted == -1)
	{
		perror(RED "Error: unclosed quote\n" WHITE);
		return (NULL);
	}
	tokens = malloc(sizeof(char *) * (tokens_counted + 1));
	if (!tokens)
		return (NULL);
	tokens[tokens_counted] = NULL;
	tokens[0] = NULL;
	return (tokens);
}

bool	init_extract_tokens(t_extract_token *extract_token,
			char *str_to_tokenize, char *separators)
{
	extract_token->index = 0;
	extract_token->token_len = 0;
	extract_token->single_quote = false;
	extract_token->double_quote = false;
	extract_token->tokens = init_tokens(str_to_tokenize, separators);
	if (!extract_token->tokens)
		return (false);
	return (true);
}

void	count_token_quoted_len(char *str_to_tokenize,
			t_extract_token *extract_tokens)
{
	extract_tokens->token_len++;
	while (str_to_tokenize[extract_tokens->token_len]
		&& str_to_tokenize[extract_tokens->token_len] != '\'')
		extract_tokens->token_len++;
	if (str_to_tokenize[extract_tokens->token_len] == '\'')
		extract_tokens->single_quote = !extract_tokens->single_quote;
	extract_tokens->token_len++;
}

void	count_token_double_quoted_len(char *str_to_tokenize,
			t_extract_token *extract_tokens)
{
	extract_tokens->token_len++;
	while (str_to_tokenize[extract_tokens->token_len]
		&& str_to_tokenize[extract_tokens->token_len] != '\"')
		extract_tokens->token_len++;
	if (str_to_tokenize[extract_tokens->token_len] == '\"')
		extract_tokens->double_quote = !extract_tokens->double_quote;
	extract_tokens->token_len++;
}

void	count_token_len(char *str_to_tokenize,
			t_extract_token *extract_tokens, char *separators)
{
	if (str_to_tokenize[extract_tokens->token_len]
		&& !is_separators(str_to_tokenize[extract_tokens->token_len],
			separators)
		&& str_to_tokenize[extract_tokens->token_len] != '\''
		&& str_to_tokenize[extract_tokens->token_len] != '\"')
	{
		while (str_to_tokenize[extract_tokens->token_len]
			&& !is_separators(str_to_tokenize[extract_tokens->token_len],
				separators)
			&& str_to_tokenize[extract_tokens->token_len] != '\''
			&& str_to_tokenize[extract_tokens->token_len] != '\"')
			extract_tokens->token_len++;
	}
}
