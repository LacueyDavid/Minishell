/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 22:03:39 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/07 12:57:37 by dlacuey          ###   ########.fr       */
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
	bool	(*function)(t_node	*node);
}			t_exec_map;

typedef struct exec_utils
{
	int			fds[NUMBER_OF_FDS];
	t_exec_map	exec_map[NUMBER_OF_EXEC_FUNCS];
	t_envs		*envs;
}				t_exec;

typedef struct pipe_utils
{
	int		fds[2];
	pid_t	*pids;
}			t_pipe;

typedef struct s_count_size
{
	size_t		size;
	size_t		index;
	ssize_t		variable_size;
	bool		double_quote;
}				t_counter;

void	do_execve(t_node *node, t_exec *exec);
void	do_builtins(t_node *node, t_exec *exec);
void	exec_full_command(t_node *node, t_exec *exec);
void	exec_simple_command(t_node *value, t_exec *exec);
void	exec_pipes(t_node *node, t_exec *exec);
void	execution(t_node *node, t_envs *envs);
bool	redirection_output(t_node *node);
bool	append_output(t_node *node);
bool	redirection_input(t_node *node);
void	close_fds(int fds[NUMBER_OF_FDS]);
void	init_exec(t_exec *exec, t_envs *envs);
void	reset_standard_streams(int fds[NUMBER_OF_FDS]);
bool	expand_env_variables(t_vector_strs *vector, t_envs *envs);
bool	fill_final_value(char *final_value, char *value, t_envs *envs);
ssize_t	count_final_value_size(char *value, t_envs *envs);
char	*get_command(char *command, char **paths);
void	wait_all_pids(pid_t *pids, int number_of_pipes);
void	expand_fail_protection(t_node *node, t_exec *exec);
void	wildcards_fail_protection(t_node *node, t_exec *exec);
void	path_fail_protection(t_node *node);
void	vector_null_protection(t_node *node, t_exec *exec);
void	remove_quotes(char **values);
size_t	count_result_of_variable(size_t *index, size_t *index2,
			char **dup_value, t_envs *envs);
ssize_t	count_actual_variable_size(char *value, t_envs *envs);
bool	fill_variables(char *final_value, char *value, t_envs *envs,
			t_counter *counter);
bool	protect_redirection(t_node *node, t_exec *exec);
void	exec_non_builtin_command(t_node *node, t_exec *exec);
void	exec_builtin_command(t_node *node, t_exec *exec);

#endif
