/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:53:01 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/14 01:20:07 by dlacuey          ###   ########.fr       */
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
	wildcards(&(node->vector_strs.values));
	if (!node->vector_strs.values)
	{
		(exit_status = 134, perror(RED"Wildcards failed"));
		clear_tree(node->head);
		exit(exit_status);
	}
	if (expand_env_variables(&(node->vector_strs), envs) == false)
	{
		(exit_status = 1, perror(RED"Expand env variables failed"WHITE));
		clear_tree(node->head);
		exit(exit_status);
	}
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	for (int i = 0; node->vector_strs.values[i]; i++)
		printf("values[%d] = %s\n", i, node->vector_strs.values[i]);
	if (!node->vector_strs.values)
	{
		(exit_status = 0);
		clear_tree(node->head);
		exit(exit_status);
	}
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
	else if (WIFSIGNALED(exit_status))
		exit_status = WTERMSIG(exit_status) + 128;
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
			exit(exit_status);
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
		exit(exit_status);
	}
	dup2(fds[0], STDIN_FILENO);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	while (index2 <= index)
	{
		waitpid(pids[index2], &exit_status, 0);
		if (WIFEXITED(exit_status))
			exit_status = WEXITSTATUS(exit_status);
		else if (WIFSIGNALED(exit_status))
			exit_status = WTERMSIG(exit_status) + 128;
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
	if (tree->number_of_pipes > 0)
		exec_pipes(tree, exec_map, fds, envs);
	else
		exec_full_command(tree, exec_map, fds, envs);
	reset_standard_streams(fds);
	close_fds(fds);
	unlink_heredoc_files(tree);
}
