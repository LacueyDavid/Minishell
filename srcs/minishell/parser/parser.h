/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 02:00:47 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/24 12:50:28 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include <stdbool.h>

typedef enum e_node_type
{
	SIMPLE_COMMAND,
	COMMAND_O_REDIRECT,
	COMMAND_I_REDIRECT,
	APPEND_REDIRECT,
	HERE_DOCUMENT,
	COMMAND_PIPE,
}					t_node_type;

typedef struct s_vector_strs
{
	size_t			size;
	size_t			capacity;
	char			**values;
}					t_vector_strs;

typedef struct s_node
{
	t_node_type		type;
	t_vector_strs	vector_strs;
	struct s_node	*head;
	struct s_node	*parent;
	struct s_node	*left;
	struct s_node	*right;
	size_t			number_of_pipes;
	size_t			number_of_here_doc;
	size_t			number_of_here_doc_index;
}					t_node;

struct	s_parser_env;

typedef struct s_parser_map
{
	bool	(*function)(struct s_parser_env * env, t_token	token);
}			t_parser_map;

typedef struct s_parser_env
{
	t_parser_map	parser_map[NUM_OF_TOKEN_TYPES];
	t_node			*head;
	t_node			*temporary;
	t_node			*simple_command;
	size_t			number_of_pipes;
}					t_parser_env;

typedef struct s_tmp_envs
{
	t_parser_env	tmp_env;
	t_token_list	*tmp1;
	t_token_list	*tmp2;
	size_t			index;
}					t_tmp_envs;

t_node			*parser(t_token_list *token_list);
t_node			*init_node(void);
bool			init_nodes(t_node **left, t_node **right);
bool			add_word(t_node *node, char *word);
bool			init_parser_env(t_parser_env *env);
bool			create_full_tree(t_parser_env *env, t_token_list *token_list);
bool			create_redirection_tree(t_parser_env *env,
					t_token_list *token_list);
bool			update_vector_strs_capacity(t_vector_strs *node);
void			clear_tree(t_node *node);
void			create_parser_map(t_parser_map parser_map[NUM_OF_TOKEN_TYPES]);
bool			add_pipe(t_parser_env *env);
t_token_list	*pipeless_token_list(t_token_list *token_list,
					size_t *index);
void			print_parser_env(t_parser_env *env);
bool			init_simple_command(t_node **simple_command, t_node *head);
bool			copy_token(t_token_list *token_list, t_token token);
bool			fill_tmp(t_token_list *token_list, t_token token);
t_vector_strs	copy_vector_strs(t_vector_strs vector_strs);
bool			add_last_command(t_parser_env *env);
bool			copy_tree(t_node *node, t_node *tmp_node);

bool			add_simple_command(t_parser_env *env, t_token token);
bool			add_append(t_parser_env *env, t_token token);
bool			add_o_redirection(t_parser_env *env, t_token token);
bool			add_i_redirection(t_parser_env *env, t_token token);
bool			add_here_doc(t_parser_env *env, t_token token);
bool			copy_env(const t_parser_env *env, t_parser_env *tmp_env_ptr);
bool			add_nodes_to_piped_tree(t_parser_env *env, t_tmp_envs *tmps,
					t_token_list *token_list);
bool			init_parser_env_piped_tree(t_tmp_envs *tmps, t_parser_env *env);
void			print_which_token(int type);
bool			check_token_list(t_token_list *token_list);

#endif
