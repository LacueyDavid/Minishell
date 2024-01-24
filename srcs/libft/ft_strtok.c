/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 20:43:12 by jdenis            #+#    #+#             */
/*   Updated: 2024/01/23 18:34:07 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include "../../includes/colors.h"

void	update_quotes_to_extract_tokens(t_extract_token *extract_tokens,
			char *str_to_tokenize)
{
	if (str_to_tokenize[extract_tokens->token_len] == '\''
		&& !extract_tokens->double_quote)
		extract_tokens->single_quote = !extract_tokens->single_quote;
	if (str_to_tokenize[extract_tokens->token_len] == '\"'
		&& !extract_tokens->single_quote)
		extract_tokens->double_quote = !extract_tokens->double_quote;
}

static void	skip_separator(char **str_to_tokenize, char *separators,
				size_t token_len)
{
	while ((*str_to_tokenize)[token_len]
		&& is_separators((*str_to_tokenize)[token_len], separators))
		(*str_to_tokenize)++;
}

static bool	fill_tokens(t_extract_token *extract_tokens, char **str_to_tokenize)
{
	if (extract_tokens->token_len > 0)
	{
		extract_tokens->tokens[extract_tokens->index]
			= extract_token(*str_to_tokenize, extract_tokens->token_len);
		if (extract_token_malloc_fail(extract_tokens->tokens,
				extract_tokens->index))
			return (false);
		(*str_to_tokenize) += extract_tokens->token_len;
		extract_tokens->index++;
		extract_tokens->token_len = 0;
	}
	return (true);
}

char	**ft_strtok(char *str_to_tokenize, char *separators)
{
	t_extract_token	extract_tokens;

	if (!init_extract_tokens(&extract_tokens, str_to_tokenize, separators))
		return (NULL);
	while (str_to_tokenize[extract_tokens.token_len])
	{
		skip_separator(&str_to_tokenize, separators, extract_tokens.token_len);
		update_quotes_to_extract_tokens(&extract_tokens, str_to_tokenize);
		if (extract_tokens.single_quote)
			count_token_quoted_len(str_to_tokenize, &extract_tokens);
		else if (extract_tokens.double_quote)
			count_token_double_quoted_len(str_to_tokenize, &extract_tokens);
		count_token_len(str_to_tokenize, &extract_tokens, separators);
		if (str_to_tokenize[extract_tokens.token_len] == '\''
			|| str_to_tokenize[extract_tokens.token_len] == '\"')
			continue ;
		if (!fill_tokens(&extract_tokens, &str_to_tokenize))
			return (NULL);
	}
	return (extract_tokens.tokens);
}
