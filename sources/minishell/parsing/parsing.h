/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 02:00:47 by dlacuey           #+#    #+#             */
/*   Updated: 2023/10/18 02:00:56 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "lexer.h"

typedef struct s_node
{
	e_token_type	type;
	char			*value;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

#endif
