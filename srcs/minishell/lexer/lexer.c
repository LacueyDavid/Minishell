/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 20:32:20 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/16 06:31:54 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

t_token_list	*lexer(char *input)
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
