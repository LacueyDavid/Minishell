/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 07:24:23 by jdenis            #+#    #+#             */
/*   Updated: 2024/02/07 12:16:42 by dlacuey          ###   ########.fr       */
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
	t_here_doc	data;

	data.fd_stdin = dup(STDIN_FILENO);
	data.heredoc_index = ft_itoa(node->head->number_of_here_doc_index);
	data.heredoc_name = ft_strjoin("here_doc.minishell", data.heredoc_index);
	data.eof = node->right->vector_strs.values[0];
	data.fd = open(data.heredoc_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data.fd < 0)
		(perror(RED "Open failed"), exit(EXIT_SUCCESS));
	while (true)
	{
		data.line = readline(LIGHT_BLUE "> " LIGHT_PINK);
		if (!data.line)
			break ;
		if (ft_strcmp(data.eof, data.line) == 0)
			break ;
		write(data.fd, data.line, ft_strlen(data.line));
		write(data.fd, "\n", 1);
		free(data.line);
	}
	dup2(data.fd_stdin, STDIN_FILENO);
	(free(data.line), free(data.heredoc_index), free(data.heredoc_name));
	close(data.fd);
	close(data.fd_stdin);
}

void	fill_heredocs(t_node *node, int fds[NUMBER_OF_FDS])
{
	if (!node || (node->type == HERE_DOCUMENT && node->right == NULL))
		return ;
	if (node->type == HERE_DOCUMENT)
	{
		node->head->number_of_here_doc_index++;
		here_doc(node);
		if (g_exit_status == 4444)
			return ;
	}
	fill_heredocs(node->left, fds);
	fill_heredocs(node->right, fds);
}

void	fork_heredocs(t_node *node, int fds[NUMBER_OF_FDS])
{
	if (!node)
		return ;
	(signal(SIGINT, SIG_IGN), signal(SIGQUIT, SIG_IGN));
	node->head->number_of_here_doc = how_many_heredocs(node);
	if (node->head->number_of_here_doc == 0)
		return ;
	signal(SIGINT, handle_heredoc);
	fill_heredocs(node, fds);
	node->head->number_of_here_doc_index = 0;
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
