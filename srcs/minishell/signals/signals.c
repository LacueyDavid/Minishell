/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 17:18:03 by dlacuey           #+#    #+#             */
/*   Updated: 2023/12/07 17:26:51 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <unistd.h>

extern int	exit_status;

void	handler_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	handle_heredoc(int sig)
{
	(void)sig;
	close(STDIN_FILENO);
	write(STDOUT_FILENO, "\n", 2);
	exit_status = 130;
}

