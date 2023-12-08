/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 08:41:00 by jdenis            #+#    #+#             */
/*   Updated: 2023/12/07 12:36:01 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "libft.h"

extern char **environ;

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
size_t	ft_strlen(char *s)
{
	size_t	index;

	index = 0;
	while (s && s[index])
		index++;
	return (index);
}

char	*ft_strdup(char *s)
{
	size_t	index;
	char	*sdup;

	sdup = malloc(ft_strlen(s) + 1);
	if (!sdup)
		return (NULL);
	index = 0;
	while (s && s[index])
	{
		sdup[index] = s[index];
		index++;
	}
	sdup[index] = '\0';
	return (sdup);
}

size_t	ft_strslen(char **strs)
{
	size_t	index;

	index = 0;
	while (strs[index])
		index++;
	return (index);
}

int	print_empty_export(void)
{
	size_t	index;

	index = 0;
	while (environ[index])
	{
		printf("declare -x %s\n", environ[index]);
		index++;
	}
	return (EXIT_SUCCESS);
}

int	add_variable(char **input)
{
	size_t	index;
	size_t	index2;

	index = ft_strslen(environ);
	environ = realloc(environ, sizeof(char *) * (ft_strslen(environ) + ft_strslen(input)));
	if (!environ)
		return (EXIT_FAILURE);
	index2 = 1;
	while (input[index2])
	{
		environ[index] = ft_strdup(input[index2]);
		if (!environ[index])
		{
			free_strs(environ);
			return (EXIT_FAILURE);
		}
		index++;
		index2++;
	}
	environ[index] = NULL;
    return (EXIT_SUCCESS);
}

int	ft_export(char **input)
{
	if (!input[1])
		return (print_empty_export());
	else
		return (add_variable(input));
}

// int main(void)
// {
// 	char *input[] = {"export", "TEST=OKBRO", "QIYANA=MAFEMME", NULL};
// 	char *input2[] = {"export", NULL};
// 	// ft_export(input2);
// 	size_t index = 0;
// 	// while (environ[index])
// 	// {
// 	// 	printf("%s\n", environ[index]);
// 	// 	index++;
// 	// }
// 	printf("taille env : %zu\n", ft_strslen(environ));
// 	ft_export(input);
// 	printf("taille env : %zu\n", ft_strslen(environ));
// 	index = 0;
// 	while (environ[index])
// 	{
// 		printf("%s\n", environ[index]);
// 		index++;
// 	}
// 	return (0);
// }