/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 06:29:17 by dlacuey           #+#    #+#             */
/*   Updated: 2023/10/24 06:42:18 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

bool	add_word(t_node *node, char *word)
{
	node->values_size++;
	if (!update_capacity(node))
		return (false);
	node->values[node->values_size - 1] = ft_strdup(word);
	if (!node->values[node->values_size - 1])
		return (false);
	node->values[node->values_size] = NULL;
	return (true);
}
