/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 08:41:00 by jdenis            #+#    #+#             */
/*   Updated: 2024/01/15 17:49:29 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"
#include "environnement.h"
#include "builtins.h"

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

char    *ft_get_name(char *input)
{
    size_t  index;
    char    *name;

    index = 0;
    while (input[index] && input[index] != '=')
        index++;
    name = malloc(sizeof(char) * (index + 1));
    if (!name)
        return NULL;
    index = 0;
    while (input[index] && input[index] != '=')
    {
        name[index] = input[index];
        index++;
    }
    name[index] = '\0';
    return (name);
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

bool    ft_is_in_env(char *name, char **envs)
{
    size_t  index;
    size_t  length;

    index = 0;
    length = ft_strlen(name);
    while (envs[index])
    {
        if (!ft_strncmp(envs[index], name, length))
            return (true);
        index++;
    }
    return (false);
}

int add_variables(t_envs *envs, char **input)
{
    char *name;

    name = ft_get_name(input[1]);
    if (ft_is_in_env(name, envs->env) == true)
        remove_environment_variable(envs->env, name);
    if (ft_is_in_env(name, envs->exports) == true)
        remove_environment_variable(envs->exports, name);
    if (add_var_env(&(envs->env), input) == EXIT_FAILURE ||
        add_var_exp(&(envs->exports), input) == EXIT_FAILURE)
    {
        free(name);
        return EXIT_FAILURE;
    }
    free(name);
    redo_envs(envs);
    return EXIT_SUCCESS;
}

bool    is_alpha_name(char *name)
{
    size_t  index;

    index = 0;
    while (name[index])
    {
        if (!ft_isalpha(name[index]))
            return (false);
        index++;
    }
    return (true);
}

int	ft_export(t_envs *envs, char **input)
{
    char *name;

	if (!input[1])
    {
		return (print_empty_export(envs));
    }
    else 
    {
        name = ft_get_name(input[1]);
        if (input[1][0] == '=' || !is_alpha_name(name))
        {
            printf("minishell: export: `%s': not a valid identifier\n", input[1]);
            free(name);
            return (EXIT_FAILURE);
        }
        free(name);
    }
    return (add_variables(envs, input));
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