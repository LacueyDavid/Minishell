/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 20:44:38 by jdenis            #+#    #+#             */
/*   Updated: 2024/01/22 10:50:56 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/colors.h"
#include "libft.h"
#include <stdio.h>

bool	is_separators(char current_char, char *separators)
{
	size_t	index;

	index = 0;
	if (!separators || !current_char)
		return (false);
	while (separators[index] != '\0')
	{
		if (current_char == separators[index])
			return (true);
		index++;
	}
	return (false);
}

size_t	current_token_len(char *str_to_tokenize, char *separators)
{
	size_t	count;

	count = 0;
	while (str_to_tokenize[count] && is_separators(str_to_tokenize[count],
			separators) == 0)
		count++;
	return (count);
}

void	free_all(char **tokens)
{
	size_t	index;

	index = 0;
	while (tokens[index])
	{
		free(tokens[index]);
		index++;
	}
	free(tokens);
}

bool	extract_token_malloc_fail(char **tokens, size_t tokens_index)
{
	if (!tokens[tokens_index])
	{
		free_all(tokens);
		return (true);
	}
	return (false);
}
