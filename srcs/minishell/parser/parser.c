/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 05:18:08 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/25 14:51:15 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "minishell_signals.h"

extern int	g_exit_status;

t_node	*parser(t_token_list *token_list)
{
	t_parser_env	env;

	if (!check_token_list(token_list))
	{
		g_exit_status = 2;
		return (NULL);
	}
	if (!init_parser_env(&env))
		return (NULL);
	if (!create_full_tree(&env, token_list))
	{
		clear_tree(env.head);
		return (NULL);
	}
	return (env.head);
}
