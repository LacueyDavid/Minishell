/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specialstrlen.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 06:26:39 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/23 15:37:27 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static void	count_special_chars(char *input, size_t *len, size_t *i)
{
	if (input[*i] == '|')
		*len += 2;
	else if ((input[*i] == '>' && input[*i + 1] == '>')
		|| (input[*i] == '<' && input[*i + 1] == '<'))
	{
		*len += 3;
		(*i)++;
	}
	else if (input[*i] == '>' || input[*i] == '<')
	{
		*len += 2;
	}
}

size_t	ft_specialstrlen(char *input)
{
	size_t	len;
	size_t	i;
	bool	single_quotes;
	bool	double_quotes;

	len = 0;
	i = 0;
	single_quotes = false;
	double_quotes = false;
	while (input[i])
	{
		update_quotes(input, &single_quotes, &double_quotes, i);
		if (!single_quotes && !double_quotes)
			count_special_chars(input, &len, &i);
		len++;
		i++;
	}
	return (len);
}
