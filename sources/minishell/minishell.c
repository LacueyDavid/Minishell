/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:58:22 by dlacuey           #+#    #+#             */
/*   Updated: 2023/10/21 05:35:44 by dlacuey          ###   ########.fr       */
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
#include "parsing.h"
#include "execution.h"

static bool is_interactive_mode(void)
{
	return (isatty(STDIN_FILENO));
}

static void	interactive_mode(void)
{
	char			*input;
	t_token_list	*token_list;
	t_node			*tree;

	while(true)
	{
		input = readline("Wesh: ");
		if (!input)
			break;
		add_history(input);
		token_list = lexer(input);
		tree = parsing(token_list);
		exec_full_command(tree);
		free(input);
		destroy_token_list(token_list);
		clear_tree(tree);
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
			break;
		delete_newline(&input);
		token_list = lexer(input);
		tree = parsing(token_list);
		exec_full_command(tree);
		free(input);
		destroy_token_list(token_list);
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
