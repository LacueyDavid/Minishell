/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_2_dimension.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 06:26:58 by dlacuey           #+#    #+#             */
/*   Updated: 2023/10/24 06:42:54 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>
#include "libft.h"
#include <stdbool.h>

bool	update_capacity(t_node *node)
{
	size_t	old_size;
	size_t	new_size;

	if (node->values_capacity == 0)
	{
		node->values_capacity = 1;
		node->values = malloc(sizeof(char *) * (node->values_capacity + 1));
	}
	if (node->values_capacity < node->values_size)
	{
		old_size = (node->values_capacity + 1) * sizeof(char *);
		node->values_capacity *= 2;
		new_size = (node->values_capacity + 1) * sizeof(char *);
		node->values = ft_realloc(node->values, new_size, old_size);
	}
	if (!node->values)
		return (false);
	return (true);
}
