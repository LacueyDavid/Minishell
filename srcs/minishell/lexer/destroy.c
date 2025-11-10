/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 02:56:55 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/15 18:32:23 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>

void	destroy_token_list(t_token_list *token_list)
{
	size_t	index;

	index = 0;
	while (index < token_list->size)
	{
		free(token_list->tokens[index].value);
		index++;
	}
	free(token_list->tokens);
	free(token_list);
}
