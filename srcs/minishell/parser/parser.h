/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 02:00:47 by dlacuey           #+#    #+#             */
/*   Updated: 2023/11/24 04:25:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include <stdbool.h>
#include "lexer.h"

typedef enum e_node_type
{
	SIMPLE_COMMAND,
	COMMAND_O_REDIRECT,
	COMMAND_I_REDIRECT,
	APPEND_REDIRECT,
	HERE_DOCUMENT,
	COMMAND_PIPE,
}   e_node_type;

typedef struct s_vector_strs
{
	size_t	size;
	size_t	capacity;
	char	**values;
}	t_vector_strs;

typedef struct s_node
{
	e_node_type		type;
	t_vector_strs	vector_strs;
	struct s_node	*head;
	struct s_node	*parent;
	struct s_node	*left;
	struct s_node	*right;
	size_t			number_of_pipes;
}	t_node;

struct s_parser_env;

typedef struct s_parser_map
{
	bool			(*function)(struct s_parser_env *env, t_token token);
}	t_parser_map;

typedef struct s_parser_env
{
	t_parser_map	parser_map[NUMBER_OF_TOKEN_TYPES];
	t_node			*head;
	t_node 			*temporary;
	t_node			*simple_command;
	size_t			number_of_pipes;
}	t_parser_env;

t_node	*parser(t_token_list *token_list);
t_node	*init_node(void);
bool	init_nodes(t_node **left, t_node **right);
bool	add_word(t_node *node, char *word);
bool	init_parser_env(t_parser_env *env);
bool	create_piped_tree(t_parser_env *env, t_token_list *token_list);
bool	create_redirection_tree(t_parser_env *env, t_token_list *token_list);
bool	update_vector_strs_capacity(t_vector_strs *node);
void	clear_tree(t_node *node);
void	create_parser_map(t_parser_map parser_map[NUMBER_OF_TOKEN_TYPES]);
bool	add_pipe(t_parser_env *env);
t_token_list	*pipeless_token_list(t_token_list *token_list, size_t *index);
void print_parser_env(t_parser_env *env);
bool	init_simple_command(t_node **simple_command, t_node *head);

#endif
