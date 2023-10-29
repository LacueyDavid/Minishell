/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 07:24:23 by jdenis            #+#    #+#             */
/*   Updated: 2023/10/29 08:46:53 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include "colors.h"
#include "libft.h"
#include "parser.h"

void	here_doc(t_node *node)
{
	char	*eof;
	char	*line;
	int		fd;

	eof = node->right->vector_strs.values[0];
	fd = open("here_doc.minishell", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		(perror(RED"Open failed"), exit(1));
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
	close(fd);
	fd = open("here_doc.minishell", O_RDONLY);
	if (dup2(fd, STDIN_FILENO) < 0)
		(perror(RED"Dup2 failed"), exit(1));
	if (close(fd) < 0)
		(perror(RED"Close failed"), exit(1));
}
