/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:48:30 by jdenis            #+#    #+#             */
/*   Updated: 2024/01/24 14:17:20 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"

char	*name_file_or_dir(struct dirent *entry, char *wildcarded_file)
{
	char	*name;

	if (ft_strchr(wildcarded_file, '/') == NULL)
		name = ft_strdup(entry->d_name);
	else
	{
		if (entry->d_type == DT_DIR)
			name = ft_strjoin(entry->d_name, "/");
		else
			name = ft_strdup(entry->d_name);
	}
	return (name);
}
