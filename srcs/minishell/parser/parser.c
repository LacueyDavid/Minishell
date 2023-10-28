/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 05:18:08 by dlacuey           #+#    #+#             */
/*   Updated: 2023/10/28 06:31:22 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>

t_node	*parser(t_token_list *token_list)
{
	t_node	*head;

	head = init_node();
	if (!head)
		return (NULL);
	head->head = head;
	if (!create_tree(head, token_list))
	{
		clear_tree(head);
		return (NULL);
	}
	return (head);
}
