/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 03:12:31 by jdenis            #+#    #+#             */
/*   Updated: 2023/12/11 14:45:56 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(t_envs *envs)
{
	char	*path;

	path = ft_getenv("PWD", envs);
	if (path == NULL)
		return (EXIT_FAILURE);
	printf("%s", path);
	free(path);
	printf("\n");
	return (EXIT_SUCCESS);
}
