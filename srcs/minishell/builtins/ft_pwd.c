/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 03:12:31 by jdenis            #+#    #+#             */
/*   Updated: 2024/01/26 20:25:00 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(t_envs *envs)
{
	char	*path;

	(void)envs;
	path = getcwd(NULL, 0);
	if (path == NULL)
		return (EXIT_FAILURE);
	printf("%s\n", path);
	free(path);
	return (EXIT_SUCCESS);
}
