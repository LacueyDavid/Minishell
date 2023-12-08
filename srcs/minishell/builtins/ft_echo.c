/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 03:12:36 by jdenis            #+#    #+#             */
/*   Updated: 2023/12/07 12:51:56 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <stdbool.h>

bool	is_white_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

size_t	skip_first_white_space(char *str)
{
	size_t index;

	index = 4;
	while (str[index] != '\0' && is_white_space(str[index]))
		index++;
	return (index);
}

void	comfirm_flag(bool *is_flag, char *str, size_t *index)
{
	*is_flag = true;
	if (str[*index] != '\0')
		*index++;
}

int skip_n(char *str, bool *is_flag) 
{
    size_t	index;
	int		index2;
	bool	all_pass;

	index = skip_first_white_space(str);
	if (str[index] == '\0')
		return (index);
	while (all_pass == false) 
	{
		if(str[index] == '-')
		{
			index2 = index;
			index++;
			while (str[index] == 'n' && str[index] != '\0')
				index++;
			if (is_white_space(str[index]) || str[index] == '\0')
				comfirm_flag(is_flag, str, &index);
			else
				return index2;
			while (is_white_space(str[index]) && str[index] != '\0')
				index++;
		}
		else
			all_pass = true;
    }
    return index;
}

int ft_echo(char *str) 
{
    int index;
    bool is_flag;

    index = skip_n(str, &is_flag);
    while (str[index] != '\0') 
	{
		if (!is_white_space(str[index]))
        	printf("%c", str[index]);
        if (str[index + 1] != '\0' && is_white_space(str[index + 1])) 
		{
            while (is_white_space(str[index + 1]) && str[index + 1] != '\0')
                index++;
			if (str[index + 1] != '\0')
            	printf(" ");
        }
        index++;
    }
    if (!is_flag)
	{
		printf("\n");
	}
	return (EXIT_SUCCESS);
}
