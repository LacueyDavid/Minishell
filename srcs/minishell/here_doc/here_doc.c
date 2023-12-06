/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 07:24:23 by jdenis            #+#    #+#             */
/*   Updated: 2023/12/06 20:43:17 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include "colors.h"
#include "libft.h"
#include "parser.h"
#include <signal.h>
#include <sys/wait.h>

extern int	exit_status;

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
		(perror(RED"Open failed"), exit(-1));
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
	free(line);
	free(heredoc_index);
	free(heredoc_name);
	close(fd);
	clear_tree(node->head);
	if (exit_status == 130)
		exit(130);
	else
		exit(0);
}
