/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deletes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 05:18:37 by dlacuey           #+#    #+#             */
/*   Updated: 2023/10/24 06:45:49 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>
#include "libft.h"

void	clear_tree(t_node *node)
{
	if (!node)
		return ;
	clear_tree(node->left);
	clear_tree(node->right);
	free_strs(node->values);
	free(node);
}
