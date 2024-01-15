/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:35:22 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/15 20:45:55 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>
#include <stdlib.h>

bool	ft_add_char(char **str, char c)
{
	char	*new_str;
	size_t	i;

	i = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(*str) + 2));
	if (!new_str)
		return (false);
	while ((*str)[i])
	{
		new_str[i] = (*str)[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	free(*str);
	*str = new_str;
	return (true);
}
