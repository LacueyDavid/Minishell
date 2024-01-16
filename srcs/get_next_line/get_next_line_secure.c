/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_secure.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 01:10:24 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/16 01:13:10 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	add_to_storage_map(int fd, t_storages *storages, int i)
{
	storages->map[i].key = fd;
	storages->size += 1;
}
