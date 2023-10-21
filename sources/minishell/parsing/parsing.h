/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 02:00:47 by dlacuey           #+#    #+#             */
/*   Updated: 2023/10/21 05:21:40 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "lexer.h"

typedef struct s_node
{
	e_token_type	type;
	size_t			values_size;
	size_t			values_capacity;
	char			**values;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

t_node	*parsing(t_token_list *token_list);
void	clear_tree(t_node *node);

#endif
