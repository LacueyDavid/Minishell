/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 03:12:36 by jdenis            #+#    #+#             */
/*   Updated: 2024/02/07 17:34:40 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <stdbool.h>

bool	is_white_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

size_t	skip_first_white_space(char *str)
{
	size_t	index;

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

int	ft_echo(char **command)
{
	int		index;
	bool	is_flag;

	is_flag = false;
	index = skip_n(command, &is_flag);
	while (command[index])
	{
		write(1, command[index], ft_strlen(command[index]));
		if (command[index + 1])
			write(1, " ", 1);
		index++;
	}
	if (!is_flag)
	{
		write(1, "\n", 1);
	}
	return (EXIT_SUCCESS);
}
