/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:58:22 by dlacuey           #+#    #+#             */
/*   Updated: 2023/11/28 00:47:54 by jdenis           ###   ########.fr       */
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

	redo_history();
	while(true)
	{
		input = readline(LIGHT_BLUE "Wesh: " LIGHT_PINK);
		write(STDOUT_FILENO, WHITE, 5);
		if (!input)
			break ;
		token_list = lexer(input);
		if (!token_list)
		{
			free(input);
			continue ;
		}
		tree = parser(token_list);
		if (!tree)
		{
			(free(input), destroy_token_list(token_list));
			continue ;
		}
		execution(tree);
		if (input[0] != '!')
			update_history(input);
		else if (exit_status == -1)
			(clear_tree(tree), destroy_token_list(token_list), exit(1));
		(free(input), destroy_token_list(token_list), clear_tree(tree));
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
		if (!token_list)
		{
			free(input);
			continue ;
		}
		tree = parser(token_list);
		if (!tree)
		{
			(free(input), destroy_token_list(token_list));
			continue ;
		}
		execution(tree);
		(free(input), destroy_token_list(token_list), clear_tree(tree));
	}
}

void	minishell(void)
{
	if (is_interactive_mode())
		interactive_mode();
	else
		non_interactive_mode();
}
