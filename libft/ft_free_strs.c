/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:02:36 by dlacuey           #+#    #+#             */
/*   Updated: 2023/07/25 16:02:38 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	free_strs(char **strs)
{
	int		index;

	index = 0;
	while (strs[index])
	{
		free(strs[index]);
		index++;
	}
	free(strs);
}
