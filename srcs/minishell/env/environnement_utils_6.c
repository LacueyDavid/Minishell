/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement_utils_6.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 20:40:05 by jdenis            #+#    #+#             */
/*   Updated: 2024/01/31 19:46:27 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environnement.h"

void	update_envs(t_envs *envs)
{
	update_env(envs);
	update_export(envs);
}

void	inutile_return(char *path)
{
	free(path);
	return ;
}
