/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 06:29:17 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/17 13:10:44 by dlacuey          ###   ########.fr       */
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
	printf("add_word: %s\n", word);
	printf("node->vector_strs.size: %zu\n", node->vector_strs.size);
	printf("node->vector_strs.capacity: %zu\n", node->vector_strs.capacity);
	node->vector_strs.values[node->vector_strs.size - 1] = ft_strdup(word);
	if (!node->vector_strs.values[node->vector_strs.size - 1])
		return (false);
	node->vector_strs.values[node->vector_strs.size] = NULL;
	printf("node->vector_strs.values: %s\n", node->vector_strs.values[node->vector_strs.size - 1]);
	printf("strlen de values: %zu\n", ft_strlen(node->vector_strs.values[node->vector_strs.size - 1]));
	return (true);
}
