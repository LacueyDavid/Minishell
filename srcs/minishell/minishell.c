/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:58:22 by dlacuey           #+#    #+#             */
/*   Updated: 2023/12/07 17:30:29 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

#include "libft.h"
#include "get_next_line.h"
#include "lexer.h"
#include "parser.h"
#include "execution.h"
#include "history.h"
#include "colors.h"
#include "minishell_signals.h"

int		exit_status = 0;

static bool is_interactive_mode(void)
{
	return (isatty(STDIN_FILENO) && isatty(STDERR_FILENO));
}

static void	interactive_mode(void)
{
	char			*input;
	t_token_list	*token_list;
	t_node			*tree;
	int				last_exit_status;

	last_exit_status = 0;
	redo_history();
	while(true)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handler_sigint_main);
		exit_status = 0;
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
		last_exit_status = exit_status;
	}
	(void)last_exit_status;
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
