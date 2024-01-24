/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 20:32:20 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/23 18:30:56 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include "colors.h"

t_token_list	*lexer(char *input)
{
	t_token_list	*token_list;
	char			**splited_input;
	char			*newinput;
	char			*separators;

	separators = ft_strdup(MINISHELL_IFS);
	token_list = init_token_list();
	if (!token_list)
		return (NULL);
	newinput = put_space_between_special_chars(input);
	if (!newinput)
		return (NULL);
	splited_input = ft_strtok(newinput, separators);
	if (!splited_input)
	{
		(free(separators), free(newinput), free(token_list));
		return (NULL);
	}
	if (!tokenize_splited_input(token_list, splited_input))
		return (NULL);
	(free_strs(splited_input), free(separators), free(newinput));
	return (token_list);
}
