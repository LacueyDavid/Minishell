/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 03:12:31 by jdenis            #+#    #+#             */
/*   Updated: 2023/10/03 18:37:44 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(char **str)
{
	char	*path;

	if (str != NULL)
	{
		printf("pwd: too many arguments");
		return (-1);
	}
	path = getcwd(NULL, 0);
	if (path == NULL)
		return (-1);
	printf("%s", path);
	free(path);
	return (1);
}
