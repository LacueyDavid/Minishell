/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_newline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:43:04 by dlacuey           #+#    #+#             */
/*   Updated: 2023/09/09 21:43:38 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void delete_newline(char **input)
{
	size_t input_size;

	input_size = ft_strlen(*input);
	if ((*input)[input_size - 1] == '\n')
		(*input)[input_size - 1] = '\0';
}
