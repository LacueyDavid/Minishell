/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 03:12:36 by jdenis            #+#    #+#             */
/*   Updated: 2023/12/04 11:20:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <stdbool.h>

bool	is_white_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

int skip_n(char *str, bool *is_flag) 
{
    int index = 4;
	int index2;
	bool all_pass;

	all_pass = false;
	while (str[index] != '\0' && is_white_space(str[index]))
		index++;
	if (str[index] == '\0')
		return index;
	while (all_pass == false) 
	{
		if(str[index] == '-')
		{
			index2 = index;
			index++;
			while (str[index] == 'n' && str[index] != '\0')
				index++;
			if (is_white_space(str[index]) || str[index] == '\0')
			{
				*is_flag = true;
				if (str[index] != '\0')
					index++;
			}
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

    is_flag = false;
    index = skip_n(str, &is_flag);
    while (str[index] != '\0') 
	{
		if (!is_white_space(str[index]))
        	printf("%c", str[index]);
        if (is_white_space(str[index + 1]) && str[index + 1] != '\0') 
		{
            while (is_white_space(str[index]) && str[index] != '\0')
                index++;
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
