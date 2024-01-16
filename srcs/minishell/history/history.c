/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 05:49:25 by jdenis            #+#    #+#             */
/*   Updated: 2024/01/16 11:00:31 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "get_next_line.h"
#include "libft.h"
#include <fcntl.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	add_input_to_history(char *input)
{
	char	*path;
	int		fd;

	path = getenv("HOME");
	if (!path)
	{
		perror(RED "Cannot find home path" WHITE);
		return ;
	}
	path = ft_strjoin(path, "/.minishell_history");
	fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(RED "Cannot open History file");
		free(path);
		return ;
	}
	write(fd, input, ft_strlen(input));
	write(fd, "\n", 1);
	close(fd);
	free(path);
}

void	redo_history(void)
{
	int		fd;
	char	*line;
	char	*path;

	path = getenv("HOME");
	if (!path)
	{
		perror(RED "Cannot find home path" WHITE);
		return ;
	}
	path = ft_strjoin(path, "/.minishell_history");
	fd = open(path, O_RDONLY | O_CREAT, 0644);
	if (fd < 0)
	{
		perror(RED "Cannot open History file");
		free(path);
		return ;
	}
	line = get_next_line(fd);
	while (line)
	{
		(delete_newline(&line), add_history(line), free(line));
		line = get_next_line(fd);
	}
	(free(line), close(fd), free(path));
}

void	update_history(char *input)
{
	add_history(input);
	add_input_to_history(input);
}
