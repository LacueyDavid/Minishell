/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:53:01 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/03 20:43:31 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <readline/readline.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include "libft.h"
#include "execution.h"
#include "colors.h"
#include "get_next_line.h"
#include "wildcards.h"
#include "minishell_signals.h"
#include "here_doc.h"
#include "environnement.h"
#include "builtins.h"

extern char	**environ;
extern int	exit_status;

bool	add_char(char **str, char c)
{
	char *new_str;
	size_t i;

	i = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(*str) + 2));
	if (!new_str)
		return false;
	while ((*str)[i])
	{
		new_str[i] = (*str)[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	free(*str);
	*str = new_str;
	return true;
}

ssize_t count_actual_variable_size(char *value, t_envs *envs)
{
	printf("je rentre dans count_actual_variable_size\n");
	size_t i = 0;
	// size_t size = 0;
	size_t n = 0;
	char *dup_value = ft_strdup(value);
	if (!dup_value)
		return -1;
	printf("dup_value = %s\n", dup_value);
	while(value[n] != '"' && value[n] != '\'' && value[n] && value[n] != '$')
		n++;
	dup_value[n] = '\0';
	if (!add_char(&dup_value, '='))
		return -1;
	printf("dup_value = %s\n", dup_value);
	while(envs->env[i] && !ft_strnstr(envs->env[i], dup_value, ft_strlen(envs->env[i])))
		i++;
	free(dup_value);
	if (!envs->env[i])
		return 0;
	printf("env[%ld] = %s\n", i, envs->env[i]);
	n = 0;
	while (envs->env[i][n] != '=')
		n++;
	dup_value = envs->env[i] + n + 1;
	printf("env[%ld] = %s\n", i, envs->env[i]);
	printf("dup_value = %s\n", dup_value);
	printf("size de dupvalue = %zu\n", ft_strlen(dup_value));
	return ft_strlen(dup_value);
}

ssize_t	count_final_value_size(char *value, t_envs *envs)
{
	(void)envs;
	size_t i = 0;
	size_t size = 0;
	ssize_t variable_size;

	while (value[i])
	{
		//le comptage ne marche pas car il faut desactiver 'asd"$a"' et
		//"asd'$a'"
		printf("size = %zu\n", size);
		printf("value[%ld] = %c\n", i, value[i]);
		if (value[i] == '$')
		{
			printf("je suis un dollar\n");
			i++;
			variable_size = count_actual_variable_size(value + i, envs);
			if (variable_size == -1)
				return -1;
			size += variable_size;
			while(value[i] != '"' && value[i] != '\'' && value[i] && value[i] != '$')
				i++;
		}
		else if (value[i] == '\'')
		{
			i++;
			while (value[i] != '\'')
			{
				size++;
				i++;
			}
			i++;
		}
		else if (value[i] == '"')
			i++;
		else
		{
			size++;
			i++;
		}
	}
	return size + 1;
}

bool	expand_value(char **values, t_envs *envs)
{
	char *value = *values;
	// char *final_value;
	ssize_t size_of_final_value;
	// size_t i = 0;

	size_of_final_value = count_final_value_size(value, envs);
	printf("size_of_final_value = %zu\n", size_of_final_value);
	printf("la value = %s\n", value);
	if (size_of_final_value == -1)
		return false;
	return true;
}

bool	expand_env_variables(char ***strs, t_envs *envs)
{
	int		i;
	char	**values = *strs;

	i = 0;
	while (values[i])
	{
		if(!expand_value(&(values[i]), envs))
			return false;
		i++;
	}
	return true;
}

void	exec_in_the_son(t_node *node, t_envs *envs)
{
	char	**paths;
	char	*command;

	paths = find_paths(environ);
	if (!paths)
	{
		(exit_status = -1, perror(RED"No paths found"WHITE));
		clear_tree(node->head);
		exit(exit_status);
	}
	if (expand_env_variables(&(node->vector_strs.values), envs) == false)
	{
		(exit_status = 1, perror(RED"Expand env variables failed"WHITE));
		clear_tree(node->head);
		exit(exit_status);
	}
	wildcards(&(node->vector_strs.values));
	if (!node->vector_strs.values)
	{
		(exit_status = 134, perror(RED"Wildcards failed"));
		clear_tree(node->head);
		exit(exit_status);
	}
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (is_a_builtin(node->vector_strs.values[0]))
	{
		free_strs(paths);
		exit_status = exec_builtin(node->vector_strs.values, envs);
		if (exit_status == -1)
			perror(RED"Exec builtins failed"WHITE);
		clear_tree(node->head);
		free_envs(envs);
		exit(exit_status);
	}
	else
	{	
		command = get_command(node->vector_strs.values[0], paths);
		free_strs(paths);
		if (!command)
		{
			(exit_status = 127, fprintf(stderr, RED"-Wesh: %s: command not found\n"WHITE, node->vector_strs.values[0]));
			clear_tree(node->head);
			exit(exit_status);
		}
		execve(command, node->vector_strs.values, envs->env);
		free_envs(envs);
		(exit_status = -1, free(command), free_envs(envs), perror(RED"Execve failed"WHITE));
		clear_tree(node->head);
		exit(exit_status);
	}
}

void	exec_simple_command(t_node *node, t_envs *envs)
{
	pid_t	pid1;

	if (!node || !node->vector_strs.values)
		return ;
	pid1 = fork();
	if (pid1 < 0)
	{
		(exit_status = -1, perror(RED"Fork failed"WHITE));
		return ;
	}
	if (pid1 == 0)
		exec_in_the_son(node, envs);
	waitpid(pid1, &exit_status, 0);
	if (WIFEXITED(exit_status))
		exit_status = WEXITSTATUS(exit_status);
}

void	exec_full_command(t_node *node, t_exec_map exec_map[NUMBER_OF_EXEC_FUNCS], int fds[NUMBER_OF_FDS], t_envs *envs)
{
	int		fd;
	char	*heredoc_name;
	char	*index_of_here_doc;

	if (!node)
		return ;
	signal(SIGINT, handler_sigint);
	signal(SIGQUIT, handler_sigint);
	if(node->type == HERE_DOCUMENT)
	{
		node->head->number_of_here_doc_index++;
		index_of_here_doc = ft_itoa(node->head->number_of_here_doc_index);
		heredoc_name = ft_strjoin("here_doc.minishell", index_of_here_doc);
		fd = open(heredoc_name, O_RDONLY);
		if (fd < 0)
		{
			(exit_status = -1, perror(RED"Open failed"WHITE));
			return ;
		}
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			(exit_status = -1, perror(RED"Dup2 failed"WHITE));
			return ;
		}
		close(fd);
		free(index_of_here_doc);
		free(heredoc_name);
	}
	else if (node->type == SIMPLE_COMMAND)
		exec_simple_command(node, envs);
	else
		exec_map[node->type].function(node);
	if (node->type != SIMPLE_COMMAND)
	{
		if (!node->left)
			exec_full_command(node->right, exec_map, fds, envs);
		else
			exec_full_command(node->left, exec_map, fds, envs);
	}
}

void exec_pipes(t_node *node, t_exec_map exec_map[NUMBER_OF_EXEC_FUNCS], int fds[NUMBER_OF_FDS], t_envs *envs)
{
	int		pipe_fds[2];
	pid_t	*pids;
	int		index;
	int		index2;

	index = 0;
	index2 = 0;
	pids = malloc(sizeof(pid_t) * (node->number_of_pipes + 1));
	if (!pids)
	{
		(exit_status = -1, perror(RED"Malloc failed"WHITE));
		return ;
	}
	while (node->type == COMMAND_PIPE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		pipe(pipe_fds);
		pids[index] = fork();
		if (pids[index] < 0)
		{
			(exit_status = -1, perror(RED"Fork failed"WHITE));
			free(pids);
			return ;
		}
		if (pids[index] == 0)
		{
			free(pids);
			dup2(pipe_fds[1], STDOUT_FILENO);
			close(pipe_fds[0]);
			close(pipe_fds[1]);
			exec_full_command(node->left, exec_map, fds, envs);
			clear_tree(node->head);
			exit(0);
		}
		node->head->number_of_here_doc_index += how_many_heredocs(node->left);
		dup2(pipe_fds[0], STDIN_FILENO);
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		node = node->right;
		index++;
	}
	pids[index] = fork();
	if (pids[index] < 0)
	{
		(exit_status = -1, perror(RED"Fork failed"WHITE));
		free(pids);
		return ;
	}
	if (pids[index] == 0)
	{
		free(pids);
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		exec_full_command(node, exec_map, fds, envs);
		clear_tree(node->head);
		exit(0);
	}
	dup2(fds[0], STDIN_FILENO);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	while (index2 <= index)
	{
		waitpid(pids[index2], &exit_status, 0);
		if (WIFEXITED(exit_status))
			exit_status = WEXITSTATUS(exit_status);
		index2++;
	}
	free(pids);
}

void	execution(t_node *tree, t_envs *envs)
{
	int fds[NUMBER_OF_FDS];
	t_exec_map	exec_map[NUMBER_OF_EXEC_FUNCS];

	signal(SIGINT, handler_sigint);
	signal(SIGQUIT, handler_sigint);
	init_fds(fds);
	init_exec_func_map(exec_map);
	fork_heredocs(tree, fds);
	if ( exit_status != 0)
	{
		unlink_heredoc_files(tree);
		return ;
	}
	if (tree->number_of_pipes > 0)
		exec_pipes(tree, exec_map, fds, envs);
	else
		exec_full_command(tree, exec_map, fds, envs);
	reset_standard_streams(fds);
	close_fds(fds);
	unlink_heredoc_files(tree);
}
