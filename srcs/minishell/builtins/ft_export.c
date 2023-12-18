/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 08:41:00 by jdenis            #+#    #+#             */
/*   Updated: 2023/12/18 16:05:00 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"
#include "environnement.h"

// extern char **environ;

int	print_empty_export(t_envs *envs)
{
	size_t	index;

	index = 0;
	while (envs->exports[index])
	{
		printf("declare -x %s\n", envs->exports[index]);
		index++;
	}
	return (EXIT_SUCCESS);
}

int add_var_exp(char ***envs, char **input)
{
    size_t index;
    size_t index2;

    index = ft_strslen(*envs);
    *envs = realloc(*envs, sizeof(char *) * (ft_strslen(*envs) + ft_strslen(input)));
    if (!*envs)
        return EXIT_FAILURE;
    index2 = 1;
    while (input[index2])
    {
        (*envs)[index] = ft_strdup_with_quotes(input[index2]);
        if (!(*envs)[index])
        {
            free_strs(*envs);
            return EXIT_FAILURE;
        }
        index++;
        index2++;
    }
    (*envs)[index] = NULL;
    return EXIT_SUCCESS;
}

int add_var_env(char ***envs, char **input)
{
    size_t index;
    size_t index2;

    index = ft_strslen(*envs);
    *envs = realloc(*envs, sizeof(char *) * (ft_strslen(*envs) + ft_strslen(input)));
    if (!*envs)
        return EXIT_FAILURE;
    index2 = 1;
    while (input[index2])
    {
        if (ft_strchr(input[index2], '='))
        {
            (*envs)[index] = ft_strdup(input[index2]);
            if (!(*envs)[index])
            {
                free_strs(*envs);
                return EXIT_FAILURE;
            }
            index++;
        }
        index2++;
    }
    (*envs)[index] = NULL;
    return EXIT_SUCCESS;
}

int add_variables(t_envs *envs, char **input)
{
    if (add_var_env(&(envs->env), input) == EXIT_FAILURE ||
        add_var_exp(&(envs->exports), input) == EXIT_FAILURE)
    {
        return EXIT_FAILURE;
    }
    redo_envs(envs);
    return EXIT_SUCCESS;
}

int	ft_export(t_envs *envs, char **input)
{
	if (!input[1])
		return (print_empty_export(envs));
    else
        return (add_variables(envs, input));
    return 0;
}

// int main(void)
// {
// 	char *input[] = {"export", "TEST=OKBRO", "QIYANA=MAFEMME", NULL};
// 	char *input2[] = {"export", NULL};
// 	t_envs *envs;
// 	envs = copy_env_and_export();
// 	// ft_export(input2, envs);
// 	print_envs(envs->env);
// 	printf("\n");
// 	print_envs(envs->exports);
// 	ft_export(envs, input);
// 	printf("\n");
// 	printf("\n");
// 	printf("\n");
// 	printf("\n");
// 	printf("\n");
// 	printf("\n");
// 	printf("\n");
// 	printf("\n");
// 	printf("\n");

// 	print_envs(envs->env);
// 	printf("\n");
// 	print_envs(envs->exports);
// 	free_envs(envs);
// 	return (0);
// }