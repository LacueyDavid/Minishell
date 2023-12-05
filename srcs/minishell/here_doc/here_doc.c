/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 07:24:23 by jdenis            #+#    #+#             */
/*   Updated: 2023/12/05 16:24:12 by dlacuey          ###   ########.fr       */
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

static void	handle_heredoc(int sig)
{
	(void)sig;
	close(STDIN_FILENO);
	write(STDOUT_FILENO, "\n", 2);
	exit(130);
}

// changer la fonction pour sigquit (mettre le status a 130 ou 0 et proteger les mallocs du fork
void	here_doc(t_node *node)
{
	char	*eof;
	char	*line;
	int		fd;
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	// les fork avec exit sont mal protegé je pense
	if (pid < 0)
		(perror(RED"Fork failed"), exit(1));
	if (pid == 0)
	{
		signal(SIGINT, handle_heredoc);
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
		exit(1);
	}
	waitpid(pid, &exit_status, 0);
	if (WIFEXITED(exit_status))
		exit_status = WEXITSTATUS(exit_status);
	else if (WIFSIGNALED(exit_status))
		exit_status = WTERMSIG(exit_status) + 128;
	fd = open("here_doc.minishell", O_RDONLY);
	if (dup2(fd, STDIN_FILENO) < 0)
		(perror(RED"Dup2 failed"), exit(1));
	if (close(fd) < 0)
		(perror(RED"Close failed"), exit(1));
}
