/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 22:03:39 by dlacuey           #+#    #+#             */
/*   Updated: 2023/10/29 09:27:28 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

#ifndef NUMBER_OF_EXEC_FUNCS
# define NUMBER_OF_EXEC_FUNCS 5
#endif

#ifndef NUMBER_OF_FDS
# define NUMBER_OF_FDS 2
#endif

#include "parser.h"

typedef struct s_exec_map
{
	void		(*function)(t_node *node);
}				t_exec_map;

void	exec_full_command(t_node *node, int fds[NUMBER_OF_FDS], t_exec_map exec_map[NUMBER_OF_EXEC_FUNCS]);
void	exec_simple_command(t_node *value);
void	execution(t_node *node);
void	here_doc(t_node *node);
void	redirection_output(t_node *node);
void	append_output(t_node *node);
void	redirection_input(t_node *node);
void	init_exec_func_map(t_exec_map exec_map[NUMBER_OF_EXEC_FUNCS]);
void	init_fds(int fds[NUMBER_OF_FDS]);
void	close_fds(int fds[NUMBER_OF_FDS]);
void	reset_standard_streams(int fds[NUMBER_OF_FDS]);

#endif
