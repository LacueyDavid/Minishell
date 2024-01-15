/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 22:03:39 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/15 18:31:06 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# ifndef NUMBER_OF_EXEC_FUNCS
#  define NUMBER_OF_EXEC_FUNCS 5
# endif

# ifndef NUMBER_OF_FDS
#  define NUMBER_OF_FDS 2
# endif

# include "environnement.h"
# include "parser.h"

typedef struct s_exec_map
{
	void	(*function)(t_node *node);
}			t_exec_map;

void		exec_full_command(t_node *node,
				t_exec_map exec_map[NUMBER_OF_EXEC_FUNCS],
				int fds[NUMBER_OF_FDS], t_envs *envs);
void		exec_simple_command(t_node *value, t_envs *envs);
void		execution(t_node *node, t_envs *envs);
void		redirection_output(t_node *node);
void		append_output(t_node *node);
void		redirection_input(t_node *node);
void		init_exec_func_map(t_exec_map exec_map[NUMBER_OF_EXEC_FUNCS]);
void		init_fds(int fds[NUMBER_OF_FDS]);
void		close_fds(int fds[NUMBER_OF_FDS]);
void		reset_standard_streams(int fds[NUMBER_OF_FDS]);
bool		expand_env_variables(t_vector_strs *vector, t_envs *envs);
bool		fill_final_value(char *final_value, char *value, t_envs *envs);
ssize_t		count_final_value_size(char *value, t_envs *envs);

#endif
