/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 08:41:00 by jdenis            #+#    #+#             */
/*   Updated: 2024/02/06 16:59:40 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "environnement.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// extern char **environ;

int	add_variables(t_envs *envs, char **input)
{
	char	*name;

	name = ft_get_name(input[1]);
	if (ft_is_in_env(name, envs->env) == true)
		remove_environment_variable(envs->env, name);
	if (ft_is_in_env(name, envs->exports) == true)
		remove_environment_variable(envs->exports, name);
	if (add_var_env(&(envs->env), input) == EXIT_FAILURE
		|| add_var_exp(&(envs->exports), input) == EXIT_FAILURE)
	{
		free(name);
		return (EXIT_FAILURE);
	}
	free(name);
	return (EXIT_SUCCESS);
}

bool	is_alpha_name(char *name)
{
	size_t	index;
	char	*tmp;

	tmp = ft_get_name(name);
	index = 0;
	while (tmp[index])
	{
		if (!ft_isalpha(tmp[index]))
		{
			free(tmp);
			return (false);
		}
		index++;
	}
	free(tmp);
	return (true);
}

int	ft_export(t_envs *envs, char **input)
{
	// char	*name;
	if (!input[1])
	{
		return (print_empty_export(envs));
	}
	// else
	// {
	// 	name = ft_get_name(input[1]);
	// 	if (input[1][0] == '=' || !is_alpha_name(name))
	// 	{
	// 		printf("minishell: export: `%s': not a valid identifier\n",
	// 			input[1]);
	// 		free(name);
	// 		return (EXIT_FAILURE);
	// 	}
	// 	free(name);
	// }
	return (add_variables(envs, input));
}
