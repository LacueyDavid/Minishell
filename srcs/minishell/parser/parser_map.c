/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 21:07:39 by jdenis            #+#    #+#             */
/*   Updated: 2024/01/15 21:08:19 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	create_parser_map(t_parser_map parser_map[NUM_OF_TOKEN_TYPES])
{
	parser_map[WORD].function = add_simple_command;
	parser_map[O_REDIRECTION].function = add_o_redirection;
	parser_map[I_REDIRECTION].function = add_i_redirection;
	parser_map[APPEND_REDIRECTION].function = add_append;
	parser_map[HERE_DOC].function = add_here_doc;
}
