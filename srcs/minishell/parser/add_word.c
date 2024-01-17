/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 06:29:17 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/17 14:17:25 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <stdio.h>

bool	add_word(t_node *node, char *word)
{
	node->vector_strs.size++;
	if (!update_vector_strs_capacity(&node->vector_strs))
		return (false);
	node->vector_strs.values[node->vector_strs.size - 1] = ft_strdup(word);
	if (!node->vector_strs.values[node->vector_strs.size - 1])
		return (false);
	node->vector_strs.values[node->vector_strs.size] = NULL;
	return (true);
}
