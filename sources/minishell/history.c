/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 05:49:25 by jdenis            #+#    #+#             */
/*   Updated: 2023/10/24 07:34:31 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"
#include "libft.h"
#include <readline/history.h>


void add_input_to_history(char *input)
{
    int fd = open(".minishell_history", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) 
	{
        perror("Cannot open History file");
        return ;
    }
    write(fd, input, ft_strlen(input));
    write(fd, "\n", 1);
    close(fd);
}

void	redo_history(void)
{
	int		fd;
	char	*line;

	fd = open(".minishell_history", O_RDONLY);
	if (fd == -1)
	{
		perror("Cannot open History file");
		return ;
	}
	line = get_next_line(fd);
	while (line)
	{
		delete_newline(&line);
		add_history(line);
		line = get_next_line(fd);
	}
	close(fd);

}

void	update_history(char *input)
{
	add_history(input);
	add_input_to_history(input);
}