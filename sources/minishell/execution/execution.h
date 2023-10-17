/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 22:03:39 by dlacuey           #+#    #+#             */
/*   Updated: 2023/10/17 01:43:42 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

#include "../lexing/lexer.h"

typedef enum e_node_type
{
	SIMPLE_COMMAND,
	IO_REDIRECTION
}   t_node_type;

typedef struct s_node
{
	t_node_type	type;
	char			*value;
	struct t_node	*left;
	struct t_node	*right;
}	t_node;

void	exec_full_command(t_node *node);
void	exec_simple_command(char *input);

#endif
