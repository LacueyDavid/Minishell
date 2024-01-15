/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 03:12:36 by jdenis            #+#    #+#             */
/*   Updated: 2024/01/15 16:16:43 by jdenis           ###   ########.fr       */
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
		index++;
}

// int skip_n(char *str, bool *is_flag) 
// {
//     size_t	index;
// 	int		index2;
// 	bool	all_pass;

// 	all_pass = false;
// 	index = skip_first_white_space(str);
// 	if (str[index] == '\0')
// 		return (index);
// 	while (all_pass == false) 
// 	{
// 		if(str[index] == '-')
// 		{
// 			index2 = index;
// 			index++;
// 			while (str[index] == 'n' && str[index] != '\0')
// 				index++;
// 			if (is_white_space(str[index]) || str[index] == '\0')
// 				comfirm_flag(is_flag, str, &index);
// 			else
// 				return index2;
// 			while (is_white_space(str[index]) && str[index] != '\0')
// 				index++;
// 		}
// 		else
// 			all_pass = true;
//     }
//     return (index);
// }

int	skip_n(char **strs, bool *is_flag)
{
	size_t	index;
	size_t	index2;

	index = 1;
	while (strs[index])
	{
		if (strs[index][0] == '-')
		{
			index2 = 1;
			while (strs[index][index2] == 'n' && strs[index][index2] != '\0')
				index2++;
			if (strs[index][index2] == '\0')
			{
				index++;
				*is_flag = true;
			}
			else
				return (index);
		}
		else
			return (index);
	}
	return (index);
}

int ft_echo(char **command) 
{
    int index;
    bool is_flag;
	// char *str;

	// printf("str = %s\n", str);
	is_flag = false;
	// str = ft_compact_strs(command);
    index = skip_n(command, &is_flag);
	// index = 1;
	// printf("index = %d\n", index);
    while (command[index]) 
	{
		printf("%s", command[index]);
		if (command[index + 1])
			printf(" ");
		index++;
	}
	// if (!is_flag)
		// if (!is_white_space(str[index]))
        // 	printf("%c", str[index]);
        // if (str[index + 1] != '\0' && is_white_space(str[index + 1])) 
		// {
        //     while (is_white_space(str[index + 1]) && str[index + 1] != '\0')
        //         index++;
		// 	if (str[index + 1] != '\0')
        //     	printf(" ");
        // }
        // index++;
    // }
    if (!is_flag)
	{
		printf("\n");
	}
	return (EXIT_SUCCESS);
}
