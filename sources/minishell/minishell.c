/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:58:22 by dlacuey           #+#    #+#             */
/*   Updated: 2023/09/10 00:02:36 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "execution.h"
#include "get_next_line.h"

static bool is_interactive_mode(void)
{
	return (isatty(STDIN_FILENO));
}

static void	interactive_mode(void)
{
	char	*input;

	while(true)
	{
		input = readline("Wesh: ");
		if (!input)
			break;
		add_history(input);
		exec_command(input);
		free(input);
	}
}

static void	non_interactive_mode(void)
{
	char	*input;

	while(true)
	{
		input = get_next_line(STDIN_FILENO);
		if (!input)
			break;
		delete_newline(&input);
		exec_command(input);
		free(input);
	}
}

void	minishell(void)
{
	if (is_interactive_mode())
		interactive_mode();
	else
		non_interactive_mode();
}
