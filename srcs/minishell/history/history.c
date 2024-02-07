/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 05:49:25 by jdenis            #+#    #+#             */
/*   Updated: 2024/02/05 18:13:19 by jdenis           ###   ########.fr       */
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

char	*history_path(void)
{
	char	*path;

	path = getenv("HOME");
	if (!path)
		return (NULL);
	path = ft_strjoin(path, "/.minishell_history");
	return (path);
}

void	add_input_to_history(char *input)
{
	char	*path;
	int		fd;

	path = history_path();
	if (!path)
		return ;
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

int	redo_history(void)
{
	int		fd;
	char	*line;
	char	*path;

	path = history_path();
	if (!path)
		return (EXIT_FAILURE);
	fd = open(path, O_RDONLY | O_CREAT, 0644);
	if (fd < 0)
	{
		perror(RED "Cannot open History file");
		free(path);
		return (EXIT_FAILURE);
	}
	line = get_next_line(fd);
	while (line)
	{
		(delete_newline(&line), add_history(line), free(line));
		line = get_next_line(fd);
	}
	(free(line), close(fd), free(path));
	return (EXIT_SUCCESS);
}

void	update_history(char *input)
{
	add_history(input);
	add_input_to_history(input);
}
