/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 05:18:08 by dlacuey           #+#    #+#             */
/*   Updated: 2023/10/29 08:05:06 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>

t_node	*parser(t_token_list *token_list)
{
	t_parser_env	env;

	if (!init_parser_env(&env))
		return (NULL);
	if (!create_tree(&env, token_list))
	{
		clear_tree(env.head);
		return (NULL);
	}
	return (env.head->head);
}
