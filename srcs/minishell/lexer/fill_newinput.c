/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_newinput.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 06:19:36 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/23 15:23:39 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static void	update_quotes(char *input, bool *single_quotes,
							bool *double_quotes, size_t i)
{
	if (input[i] == '\'')
		if (!*double_quotes)
			*single_quotes = !*single_quotes;
	if (input[i] == '"')
		if (!*single_quotes)
			*double_quotes = !*double_quotes;
}

static void	put_space_between_append(char *oldinput, size_t *i,
									size_t *j, char *newinput)
{
	newinput[*j] = ' ';
	newinput[*j + 1] = oldinput[*i];
	newinput[*j + 2] = oldinput[*i + 1];
	newinput[*j + 3] = ' ';
	*j += 4;
	*i += 2;
}

static void	put_space_between_tokens(char *oldinput, size_t *i,
									size_t *j, char *newinput)
{
	if (oldinput[*i] == '|')
	{
		newinput[*j] = ' ';
		newinput[*j + 1] = '|';
		newinput[*j + 2] = ' ';
		*j += 3;
		(*i)++;
	}
	else if ((oldinput[*i] == '>' && oldinput[*i + 1] == '>')
		|| (oldinput[*i] == '<' && oldinput[*i + 1] == '<'))
		put_space_between_append(oldinput, i, j, newinput);
	else if (oldinput[*i] == '>' || oldinput[*i] == '<')
	{
		newinput[*j] = ' ';
		newinput[*j + 1] = oldinput[*i];
		newinput[*j + 2] = ' ';
		*j += 3;
		(*i)++;
	}
	else
	{
		newinput[*j] = oldinput[*i];
		(*j)++;
		(*i)++;
	}
}

static void	fill_newinput(char *oldinput, char *newinput, size_t newlen)
{
	bool	single_quotes;
	bool	double_quotes;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	single_quotes = false;
	double_quotes = false;
	while (oldinput[i])
	{
		update_quotes(oldinput, &single_quotes, &double_quotes, i);
		if (!single_quotes && !double_quotes)
			put_space_between_tokens(oldinput, &i, &j, newinput);
		else
		{
			newinput[j] = oldinput[i];
			j++;
			i++;
		}
	}
	newinput[newlen] = '\0';
}
