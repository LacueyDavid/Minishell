/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 08:10:19 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/23 15:38:31 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/colors.h"
#include "libft.h"
#include <stdio.h>

static void	count_quote(char *str_to_tokenize, size_t *index,
		bool *single_quote, size_t *tokens)
{
	(*index)++;
	while (str_to_tokenize[*index] && str_to_tokenize[*index] != '\'')
		(*index)++;
	if (str_to_tokenize[*index] == '\'')
		*single_quote = !*single_quote;
	if (str_to_tokenize[*index] != '\0')
		(*index)++;
	(*tokens)++;
}

static void	count_double_quote(char *str_to_tokenize, size_t *index,
		bool *double_quote, size_t *tokens)
{
	(*index)++;
	while (str_to_tokenize[*index] && str_to_tokenize[*index] != '\"')
		(*index)++;
	if (str_to_tokenize[*index] == '\"')
		*double_quote = !*double_quote;
	if (str_to_tokenize[*index] != '\0')
		(*index)++;
	(*tokens)++;
}

static void	count_word(char *str_to_tokenize, size_t *index, size_t *tokens,
		char *separators)
{
	if (str_to_tokenize[*index]
		&& !is_separators(str_to_tokenize[*index], separators)
		&& str_to_tokenize[*index] != '\''
		&& str_to_tokenize[*index] != '\"')
	{
		(*tokens)++;
		while (str_to_tokenize[*index]
			&& !is_separators(str_to_tokenize[*index], separators)
			&& str_to_tokenize[*index] != '\''
			&& str_to_tokenize[*index] != '\"')
			(*index)++;
	}
}

static void	skip_separators(char *str_to_tokenize, size_t *index,
		char *separators)
{
	while (str_to_tokenize[*index]
		&& is_separators(str_to_tokenize[*index], separators))
		(*index)++;
}

ssize_t	count_tokens(char *str_to_tokenize, char *separators)
{
	t_count	count;

	init_count(&count);
	while (str_to_tokenize[count.index])
	{
		skip_separators(str_to_tokenize, &count.index, separators);
		update_quotes_to_count_tokens(&count.single_quote, &count.double_quote,
			str_to_tokenize[count.index]);
		if (count.single_quote)
			count_quote(str_to_tokenize, &count.index,
				&count.single_quote, &count.tokens);
		else if (count.double_quote)
			count_double_quote(str_to_tokenize, &count.index,
				&count.double_quote, &count.tokens);
		count_word(str_to_tokenize, &count.index, &count.tokens, separators);
		if (str_to_tokenize[count.index] == '\"'
			|| str_to_tokenize[count.index] == '\'')
			continue ;
		if (count.tokens > 0)
			count.count++;
		count.tokens = 0;
	}
	if (count.single_quote || count.double_quote)
		return (-1);
	return (count.count);
}
