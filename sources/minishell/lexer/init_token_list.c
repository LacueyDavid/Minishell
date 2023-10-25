/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 02:59:45 by dlacuey           #+#    #+#             */
/*   Updated: 2023/10/25 03:07:09 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token_list *init_token_list(void)
{
	t_token_list *token_list;

	token_list = malloc(sizeof(t_token_list));
	if (!token_list)
		return (NULL);
	token_list->tokens = NULL;
	token_list->size = 0;
	token_list->capacity = 0;
	return (token_list);
}
