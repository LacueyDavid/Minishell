/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 02:00:47 by dlacuey           #+#    #+#             */
/*   Updated: 2023/10/26 11:12:52 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "lexer.h"
#include <stdbool.h>

typedef struct s_vector
{
	size_t		size;
	size_t		capacity;
	char		**values;
}	t_vector_strs;

typedef struct s_node
{
	e_token_type	type;
	t_vector_strs	vector_strs;
	struct s_node	*head;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

t_node	*parser(t_token_list *token_list);
t_node	*init_node(void);
void	clear_tree(t_node *node);
bool	add_word(t_node *node, char *word);
bool	init_nodes(t_node **left, t_node **right);
bool	create_tree(t_node *node, t_token_list *token_list);
bool	update_vector_strs_capacity(t_vector_strs *node);

#endif
