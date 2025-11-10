/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 08:37:16 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/06 19:06:44 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "libft.h"
#include "parser.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

bool	redirection_output(t_node *node)
{
	int	fd;

	fd = open(node->right->vector_strs.values[0], O_WRONLY | O_CREAT | O_TRUNC,
			0644);
	if (fd < 0)
		return (perror(RED "Open failed" WHITE), false);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (perror(RED "Dup2 failed" WHITE), false);
	if (close(fd) < 0)
		return (perror(RED "Close failed" WHITE), false);
	return (true);
}

bool	append_output(t_node *node)
{
	int	fd;

	fd = open(node->right->vector_strs.values[0], O_WRONLY | O_CREAT | O_APPEND,
			0644);
	if (fd < 0)
		return (perror(RED "Open failed" WHITE), false);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (perror(RED "Dup2 failed" WHITE), false);
	if (close(fd) < 0)
		return (perror(RED "Close failed" WHITE), false);
	return (true);
}

bool	redirection_input(t_node *node)
{
	int	fd;

	fd = open(node->right->vector_strs.values[0], O_RDONLY);
	if (fd < 0)
		return (perror(RED "Open failed" WHITE), false);
	if (dup2(fd, STDIN_FILENO) < 0)
		return (perror(RED "Dup2 failed" WHITE), false);
	if (close(fd) < 0)
		return (perror(RED "Close failed" WHITE), false);
	return (true);
}
