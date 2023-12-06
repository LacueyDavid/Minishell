/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:53:01 by dlacuey           #+#    #+#             */
/*   Updated: 2023/12/06 20:43:17 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "execution.h"
#include "fcntl.h"
#include <sys/wait.h>
#include <stdio.h>
#include "colors.h"
#include "get_next_line.h"
#include <readline/readline.h>
#include "wildcards.h"
#include <sys/types.h>
#include <unistd.h>

extern char	**environ;
extern int	exit_status;


static void	handler_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	exec_in_the_son(t_node *node)
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
	command = get_command(node->vector_strs.values[0], paths);
	free_strs(paths);
	if (!command)
	{
		(exit_status = 127, fprintf(stderr, RED"-Wesh: %s: command not found\n"WHITE, node->vector_strs.values[0]));
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
	execve(command, node->vector_strs.values, environ);
	(exit_status = -1, free(command), perror(RED"Execve failed"WHITE));
	clear_tree(node->head);
	exit(exit_status);
}

void	exec_simple_command(t_node *node)
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
		exec_in_the_son(node);
	waitpid(pid1, &exit_status, 0);
	if (WIFEXITED(exit_status))
		exit_status = WEXITSTATUS(exit_status);
}

void	exec_full_command(t_node *node, t_exec_map exec_map[NUMBER_OF_EXEC_FUNCS], int fds[NUMBER_OF_FDS])
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
	else
		exec_map[node->type].function(node);
	if (node->type != SIMPLE_COMMAND)
	{
		if (!node->left)
			exec_full_command(node->right, exec_map, fds);
		else
			exec_full_command(node->left, exec_map, fds);
	}
}

size_t	how_many_heredocs(t_node *node)
{
	size_t value;

	value = 0;
	if (!node)
		return 0;
	if (node->type == HERE_DOCUMENT)
		value = 1;
	if (node->right == NULL && node->type == HERE_DOCUMENT)
		return 0;
	return how_many_heredocs(node->left) + how_many_heredocs(node->right) + value;
}

void exec_pipes(t_node *node, t_exec_map exec_map[NUMBER_OF_EXEC_FUNCS], int fds[NUMBER_OF_FDS])
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
			exec_full_command(node->left, exec_map, fds);
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
		exec_full_command(node, exec_map, fds);
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

static void	handle_heredoc(int sig)
{
	(void)sig;
	close(STDIN_FILENO);
	write(STDOUT_FILENO, "\n", 2);
	exit_status = 130;
}

void	fill_heredocs(t_node *node, int fds[NUMBER_OF_FDS])
{
	if (!node)
		return ;
	if (node->type == HERE_DOCUMENT)
	{
		node->head->number_of_here_doc_index++;
		printf("number of here doc index: %ld\n", node->head->number_of_here_doc_index);
		printf("number of here doc: %ld\n", node->head->number_of_here_doc);
		here_doc(node);
	}
	fill_heredocs(node->left, fds);
	fill_heredocs(node->right, fds);
}

void	fork_heredocs(t_node *node, int fds[NUMBER_OF_FDS])
{
	pid_t	pid;

	if (!node)
		return ;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	node->head->number_of_here_doc = how_many_heredocs(node);
	pid = fork();
	if (pid < 0)
		(perror(RED"Fork failed"), exit(1));
	if (pid == 0)
	{
		signal(SIGINT, handle_heredoc);
		fill_heredocs(node, fds);
		exit(0);
	}
	waitpid(pid, &exit_status, 0);
	if (WIFEXITED(exit_status))
		exit_status = WEXITSTATUS(exit_status);
	else if (WIFSIGNALED(exit_status))
		exit_status = WTERMSIG(exit_status) + 128;
}

// void	unlink_heredoc_files(t_node *node)
// {
// 	char	*heredoc_name;
// 	size_t	index;
// 	char	*index_str;
//
// 	if (!node)
// 		return ;
// 	index = 1;
// 	while(index <= node->number_of_here_doc)
// 	{
// 		index_str = ft_itoa(index);
// 		heredoc_name = ft_strjoin("here_doc.minishell", index_str);
// 		unlink(heredoc_name);
// 		free(index_str);
// 		free(heredoc_name);
// 		index++;
// 	}
// }

void	execution(t_node *tree)
{
	int fds[NUMBER_OF_FDS];
	t_exec_map	exec_map[NUMBER_OF_EXEC_FUNCS];

	tree->head->number_of_here_doc = 0;
	tree->head->number_of_here_doc_index = 0;
	signal(SIGINT, handler_sigint);
	signal(SIGQUIT, handler_sigint);
	init_fds(fds);
	init_exec_func_map(exec_map);
	fork_heredocs(tree, fds);
	if ( exit_status != 0)
		return ;
	if (tree->number_of_pipes > 0)
		exec_pipes(tree, exec_map, fds);
	else
		exec_full_command(tree, exec_map, fds);
	reset_standard_streams(fds);
	close_fds(fds);
	// unlink_heredoc_files(tree);
	tree->head->number_of_here_doc = 0;
	tree->head->number_of_here_doc_index = 0;
}
