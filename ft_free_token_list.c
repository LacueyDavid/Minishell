/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_token_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 20:04:04 by dlacuey           #+#    #+#             */
/*   Updated: 2023/09/29 20:08:30 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

free_token_list(t_token_list *token_list)
{
	size_t index;

	index = 0;
	while (index < token_list->size)
	{
		free(token_list->tokens[index].value);
		token_list->tokens[index].value = NULL;
		index++;
	}
	free(token_list->tokens);
	free(token_list);
}
