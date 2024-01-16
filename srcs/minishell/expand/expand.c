/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 19:13:22 by marvin            #+#    #+#             */
/*   Updated: 2023/12/21 19:13:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include <stdio.h>
#include <stdlib.h>

// #include "environnment.h"

char	*get_name(char	*input, size_t index)
{
	size_t	length;
	size_t	index_tmp;
	char	*name;

	length = 0;
	if (input[index] != '$')
		return NULL;
	else
		index ++;
	index_tmp = index;
	while (input[index_tmp] && input[index_tmp] != ' ')
	{
		length++;
		index_tmp++;
	}
	index_tmp = 0;
	name = malloc(sizeof(char) * (length + 1));
	while (input[index] && input[index] != ' ')
	{
		name[index_tmp] = input[index];
		index++;
		index_tmp++;
	}
	name[index_tmp] = '\0';
	return (name);
}

// char	*handle_variable(char *input)
// {
// 	size_t	index;
// 	char	*variable_name;
// 	char	*variable_value;

// 	index = 0;
// 	while (input[index])
// 	{
// 		if (input[index] == '$')
// 		{
// 			variable_name = get_name(input, index);
// 			if (variable_name)
// 			{
// 				input = change_variable(variable_name, input, envs)
// 				free(variable_name);
// 				index = 0;
// 			}
// 		}
// 		else
// 			index++;
// 	}
// 	return (input);
// }

// char	*expand_input(char *input)
// {
// 	size_t	index;

// 	index = 0;
// 	while (input[index])
// 	{

// 	}
// }

int main(void)
{
	char *input = "echo $TOTO $POLO";
	char *name = get_name(input, 5);
	printf("premier name vaut : %s\n", name);
	free(name);
	name = get_name(input, 11);
	printf("deuxieme name vaut : %s\n", name);
	free(name);
	return 0;
}