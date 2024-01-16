/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 07:24:23 by jdenis            #+#    #+#             */
/*   Updated: 2024/01/16 10:59:11 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "here_doc.h"
#include "libft.h"
#include "minishell_signals.h"
#include "parser.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

extern int	g_exit_status;

void	here_doc(t_node *node)
{
	char	*eof;
	char	*line;
	int		fd;
	char	*heredoc_name;
	char	*heredoc_index;

	heredoc_index = ft_itoa(node->head->number_of_here_doc_index);
	heredoc_name = ft_strjoin("here_doc.minishell", heredoc_index);
	eof = node->right->vector_strs.values[0];
	fd = open(heredoc_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		(perror(RED "Open failed"), exit(EXIT_SUCCESS));
	while (true)
	{
		line = readline(LIGHT_BLUE "> " LIGHT_PINK);
		if (!line)
			break ;
		if (ft_strcmp(eof, line) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	(free(line), free(heredoc_index), free(heredoc_name));
	close(fd);
}

void	fill_heredocs(t_node *node, int fds[NUMBER_OF_FDS])
{
	if (!node || (node->type == HERE_DOCUMENT && node->right == NULL))
		return ;
	if (node->type == HERE_DOCUMENT)
	{
		node->head->number_of_here_doc_index++;
		here_doc(node);
		if (g_exit_status == 130)
		{
			clear_tree(node->head);
			exit(130);
		}
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
	if (node->head->number_of_here_doc == 0)
		return ;
	pid = fork();
	if (pid < 0)
		(perror(RED "Fork in fork heredocs failed" WHITE), exit(1));
	if (pid == 0)
	{
		signal(SIGINT, handle_heredoc);
		fill_heredocs(node, fds);
		clear_tree(node->head);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, &g_exit_status, 0);
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	else if (WIFSIGNALED(g_exit_status))
		g_exit_status = WTERMSIG(g_exit_status) + 128;
}

void	unlink_heredoc_files(t_node *node)
{
	char	*heredoc_name;
	size_t	index;
	char	*index_str;

	if (!node)
		return ;
	index = 1;
	while (index <= node->number_of_here_doc)
	{
		index_str = ft_itoa(index);
		heredoc_name = ft_strjoin("here_doc.minishell", index_str);
		unlink(heredoc_name);
		free(index_str);
		free(heredoc_name);
		index++;
	}
}

size_t	how_many_heredocs(t_node *node)
{
	size_t	value;

	value = 0;
	if (!node)
		return (0);
	if (node->type == HERE_DOCUMENT)
		value = 1;
	if (node->right == NULL && node->type == HERE_DOCUMENT)
		return (0);
	return (how_many_heredocs(node->left) + how_many_heredocs(node->right)
		+ value);
}
