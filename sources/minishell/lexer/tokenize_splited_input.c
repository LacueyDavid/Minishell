/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_splited_input.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 03:10:40 by dlacuey           #+#    #+#             */
/*   Updated: 2023/10/25 03:19:19 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lexer.h"
#include "libft.h"

static t_token create_token(int type, char *value)
{
	t_token	token;

	token.type = type;
	token.value = ft_strdup(value);
	return (token);
}

static t_token choose_token(char *input)
{
	t_token	token;

	if (ft_strcmp(input, ">") == 0)
		token = create_token(O_REDIRECTION, input);
	else
		token = create_token(WORD, input);
	return (token);
}

bool tokenize_splited_input(t_token_list *token_list, char **splited_input)
{
	t_token			token;

	while (*splited_input)
	{
		token = choose_token(*splited_input);
		if (!token.value)
		{
			destroy_token_list(token_list);
			return (false);
		}
		add_token(token_list, token);
		splited_input++;
	}
	return (true);
}
