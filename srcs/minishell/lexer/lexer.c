/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 20:32:20 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/14 02:27:48 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer.h"
#include "libft.h"

#include <stdio.h>
static size_t ft_specialstrlen(char *input)
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
		if(input[i] == '\'')
			if (!double_quotes)
				single_quotes = !single_quotes;
		if(input[i] == '"')
			if (!single_quotes)
				double_quotes = !double_quotes;
		if (!single_quotes && !double_quotes)
		{
			if (input[i] == '|')
				len += 2;
			else if ((input[i] == '>' && input[i + 1] == '>')
					 || (input[i] == '<' && input[i + 1] == '<'))
			{
				len += 3;
				i++;
			}
			else if (input[i] == '>' || input[i] == '<')
				len += 2;
			len++;
		}
		else
			len++;
		i++;
	}
	return (len);
}

static void put_space_between_special_chars(char **input)
{
	char *oldinput = *input;
	size_t newlen = ft_specialstrlen(oldinput);
	char *newinput = malloc(sizeof(char) * (newlen + 1));
	bool	single_quotes;
	bool	double_quotes;
	size_t i = 0;
	size_t j = 0;

	single_quotes = false;
	double_quotes = false;
	while (oldinput[i])
	{
		if(oldinput[i] == '\'')
			if (!double_quotes)
				single_quotes = !single_quotes;
		if(oldinput[i] == '"')
			if (!single_quotes)
				double_quotes = !double_quotes;
		if (!single_quotes && !double_quotes)
		{
			if (oldinput[i] == '|')
			{
				newinput[j] = ' ';
				newinput[j+1] = '|';
				newinput[j+2] = ' ';
				j += 3;
				i++;
			}
			else if ((oldinput[i] == '>' && oldinput[i + 1] == '>')
					 || (oldinput[i] == '<' && oldinput[i + 1] == '<'))
			{
				newinput[j] = ' ';
				newinput[j+1] = oldinput[i];
				newinput[j+2] = oldinput[i + 1];
				newinput[j+3] = ' ';
				j += 4;
				i+=2;
			}
			else if (oldinput[i] == '>' || oldinput[i] == '<')
			{
				newinput[j] = ' ';
				newinput[j+1] = oldinput[i];
				newinput[j+2] = ' ';
				j += 3;
				i++;
			}
			else
			{
				newinput[j] = oldinput[i];
				j++;
				i++;
			}
		}
		else
		{
			newinput[j] = oldinput[i];
			j++;
			i++;
		}
	}
	newinput[newlen] = '\0';
	*input = newinput;
}

t_token_list *lexer(char *input)
{
	t_token_list	*token_list;
	char			**splited_input;

	token_list = init_token_list();
	if (!token_list)
		return (NULL);
	put_space_between_special_chars(&input);
	splited_input = ft_strtok(input, MINISHELL_IFS);
	if (!splited_input)
	{
		free(token_list);
		return (NULL);
	}
	if (!tokenize_splited_input(token_list, splited_input))
		return (NULL);
	free_strs(splited_input);
	free(input);
	return (token_list);
}
