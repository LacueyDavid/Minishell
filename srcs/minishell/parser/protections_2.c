/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protections_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 05:18:08 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/24 12:48:12 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

void	print_which_token(int type)
{
	if (type == PIPE)
		printf("wesh: syntax error near unexpected token `|'\n");
	else if (type == O_REDIRECTION)
		printf("wesh: syntax error near unexpected token `>'\n");
	else if (type == I_REDIRECTION)
		printf("wesh: syntax error near unexpected token `<'\n");
	else if (type == APPEND_REDIRECTION)
		printf("wesh: syntax error near unexpected token `>>'\n");
	else if (type == HERE_DOC)
		printf("wesh: syntax error near unexpected token `<<'\n");
	else
		printf("wesh: syntax error near unexpected token `newline'\n");
}
