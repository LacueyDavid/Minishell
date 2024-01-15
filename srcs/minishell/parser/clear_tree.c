/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 05:18:37 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/15 18:33:08 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <stdlib.h>

void	clear_tree(t_node *node)
{
	if (!node)
		return ;
	clear_tree(node->left);
	clear_tree(node->right);
	free_strs(node->vector_strs.values);
	free(node);
}
