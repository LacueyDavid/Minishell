/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 03:12:36 by jdenis            #+#    #+#             */
/*   Updated: 2023/10/03 18:37:39 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	help_n_option(char **str)
{
	int	index;

	index = 1;
	if (str[0][0] == '-' && str[0][1] == 'n')
	{
		while (str[0][index])
		{
			if (str[0][index] == 'n')
				index++;
			else
				return (0);
		}
		return (1);
	}
	else
		return (0);
}

void	ft_echo(char **str)
{
	int	index;
	int	is_flag;

	is_flag = help_n_option(str);
	index = is_flag;
	while (str[index])
	{
		printf("%s", str[index]);
		if (str[index + 1])
			printf(" ");
		else
			break ;
		index++;
	}
	if (is_flag == 0)
		printf("\n");
}

// int	main(void)
// {
// 	char *input[4] = {"-nnnnnnnnnnn", "hello", "wolrd", 0};
// 	ft_echo(input);
// 	return (0);
// }