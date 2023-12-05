/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:58:22 by dlacuey           #+#    #+#             */
/*   Updated: 2023/12/05 16:24:36 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "get_next_line.h"
#include "lexer.h"
#include "parser.h"
#include "execution.h"
#include "history.h"
#include "colors.h"
#include <signal.h>

int		exit_status = 0;

static bool is_interactive_mode(void)
{
	return (isatty(STDIN_FILENO) && isatty(STDERR_FILENO));
}

static void handler_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	interactive_mode(void)
{
	char			*input;
	t_token_list	*token_list;
	t_node			*tree;

	redo_history();
	while(true)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handler_sigint);
		input = readline(LIGHT_BLUE "Wesh: " LIGHT_PINK);
		write(STDOUT_FILENO, WHITE, 5);
		if (!input)
			break ;
		if (input[0] != '!')
			update_history(input);
		token_list = lexer(input);
		free(input);
		if (!token_list)
			continue ;
		tree = parser(token_list);
		destroy_token_list(token_list);
		if (!tree)
			continue ;
		execution(tree);
		clear_tree(tree);
		if (exit_status == -1)
			exit(1);
	}
}

static void	non_interactive_mode(void)
{
	char			*input;
	t_token_list	*token_list;
	t_node			*tree;

	while(true)
	{
		input = get_next_line(STDIN_FILENO);
		if (!input)
			break ;
		delete_newline(&input);
		token_list = lexer(input);
		free(input);
		if (!token_list)
			continue ;
		tree = parser(token_list);
		destroy_token_list(token_list);
		if (!tree)
			continue ;
		execution(tree);
		clear_tree(tree);
	}
}

void	minishell(void)
{
	if (is_interactive_mode())
		interactive_mode();
	else
		non_interactive_mode();
}
