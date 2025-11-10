/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 08:12:14 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/16 08:16:39 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	init_count(t_count *count)
{
	count->single_quote = false;
	count->double_quote = false;
	count->count = 0;
	count->index = 0;
	count->tokens = 0;
}

void	update_quotes_to_count_tokens(bool *single_quote, bool *double_quote,
		char current_char)
{
	if (current_char == '\'')
		*single_quote = !*single_quote;
	if (current_char == '\"')
		*double_quote = !*double_quote;
}
