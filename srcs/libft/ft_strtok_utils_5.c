/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_utils_5.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:51:53 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/17 14:18:05 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include "../../includes/colors.h"

char	*extract_token(char *str_to_tokenize, size_t token_size)
{
	char	*token;
	size_t	index;

	index = 0;
	token = malloc(sizeof(char) * (token_size + 1));
	if (!token)
		return (NULL);
	while (index < token_size)
	{
		token[index] = str_to_tokenize[index];
		index++;
	}
	token[index] = '\0';
	return (token);
}
