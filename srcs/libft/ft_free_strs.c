/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:02:36 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/15 20:43:47 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	free_strs(char **strs)
{
	size_t	index;

	index = 0;
	if (!strs)
		return ;
	while (strs[index])
	{
		free(strs[index]);
		index++;
	}
	free(strs);
}
