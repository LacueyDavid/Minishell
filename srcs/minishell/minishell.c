/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 17:51:11 by jdenis            #+#    #+#             */
/*   Updated: 2024/02/07 16:03:07 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

#include "libft.h"
#include "builtins.h"
#include "get_next_line.h"
#include "lexer.h"
#include "parser.h"
#include "execution.h"
#include "history.h"
#include "colors.h"
#include "minishell_signals.h"
#include "environnement.h"

int		g_exit_status = 0;

void	envs_handler(t_envs	*envs)
{
	char			*shlvl_str;
	int				shlvl;

	shlvl_str = ft_getenv("SHLVL", envs);
	if (!shlvl_str)
		return ;
	shlvl = ft_atoi(shlvl_str);
	free(shlvl_str);
	shlvl_str = ft_getenv("SHLVL", envs);
	if (!shlvl_str)
		return ;
	if (shlvl > ft_atoi(shlvl_str))
	{
		free(shlvl_str);
		free_envs(envs);
		exit(g_exit_status);
	}
	free(shlvl_str);
}

static void	interactive_mode(t_envs *envs)
{
	char			*input;
	t_token_list	*token_list;
	t_node			*tree;

	while (true)
	{
		if (g_exit_status == 4444)
			g_exit_status = 4442;
		(signal(SIGQUIT, SIG_IGN), signal(SIGINT, handler_sigint_main));
		input = readline(LIGHT_BLUE "Wesh: " LIGHT_PINK);
		write(STDOUT_FILENO, WHITE, ft_strlen(WHITE));
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
		(execution(tree, envs), clear_tree(tree->head), envs_handler(envs));
	}
}

static void	non_interactive_mode(t_envs *envs)
{
	char			*input;
	t_token_list	*token_list;
	t_node			*tree;

	while (true)
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
		(execution(tree, envs), clear_tree(tree->head), envs_handler(envs));
	}
}

static bool	is_interactive_mode(void)
{
	return (isatty(STDIN_FILENO) && isatty(STDERR_FILENO));
}

void	minishell(void)
{
	t_envs			*envs;

	envs = copy_env_and_export();
	if (!envs)
		return ;
	if (is_interactive_mode())
	{
		redo_history();
		interactive_mode(envs);
	}
	else
		non_interactive_mode(envs);
	free_envs(envs);
}
