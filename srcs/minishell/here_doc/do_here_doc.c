/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 04:38:50 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/05 18:54:02 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "colors.h"
#include "environnement.h"
#include "execution.h"
#include "get_next_line.h"
#include "here_doc.h"
#include "libft.h"
#include "minishell_signals.h"
#include "wildcards.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

extern int	g_exit_status;

void	do_here_doc(t_node *node)
{
	char	*heredoc_name;
	char	*index_of_here_doc;
	int		fd;

	node->head->number_of_here_doc_index++;
	index_of_here_doc = ft_itoa(node->head->number_of_here_doc_index);
	heredoc_name = ft_strjoin("here_doc.minishell", index_of_here_doc);
	fd = open(heredoc_name, O_RDONLY);
	if (fd < 0)
	{
		g_exit_status = -1;
		perror(RED "Open failed" WHITE);
		return ;
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		g_exit_status = -1;
		perror(RED "Dup2 failed" WHITE);
		return ;
	}
	close(fd);
	free(index_of_here_doc);
	free(heredoc_name);
}
