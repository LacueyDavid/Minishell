/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:02:36 by dlacuey           #+#    #+#             */
/*   Updated: 2023/10/21 04:34:07 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	free_strs(char **strs)
{
	size_t index;

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
