/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_vector_strs_capacity.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 06:26:58 by dlacuey           #+#    #+#             */
/*   Updated: 2023/10/26 12:27:46 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>
#include "libft.h"
#include <stdbool.h>

bool	update_vector_strs_capacity(t_vector_strs *vector_strs)
{
	size_t	old_size;
	size_t	new_size;

	if (vector_strs->capacity == 0)
	{
		vector_strs->capacity = 1;
		vector_strs->values = malloc(sizeof(char *) * (vector_strs->capacity + 1));
	}
	if (vector_strs->capacity < vector_strs->size)
	{
		old_size = (vector_strs->capacity + 1) * sizeof(char *);
		vector_strs->capacity *= 2;
		new_size = (vector_strs->capacity + 1) * sizeof(char *);
		vector_strs->values = ft_realloc(vector_strs->values, new_size, old_size);
	}
	if (!vector_strs->values)
		return (false);
	return (true);
}
