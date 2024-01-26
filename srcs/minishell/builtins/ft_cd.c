/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/12/04 11:37:33 by marvin            #+#    #+#             */
/*   Updated: 2023/12/04 11:37:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "environnement.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	change_pwds(char *pwd, t_envs *envs, char *new_path)
{
	if (chdir(new_path))
	{
		perror("cd");
		return (EXIT_FAILURE);
	}
	ft_setenv("OLDPWD", pwd, envs);
	free(pwd);
	pwd = getcwd(NULL, 0);
	ft_setenv("PWD", pwd, envs);
	free(pwd);
	return (EXIT_SUCCESS);
}

int	ft_cd(t_envs *envs, char *command)
{
	int		g_exit_status;
	char	*pwd;
	char	*new_path;

	g_exit_status = EXIT_SUCCESS;
	pwd = ft_getenv("PWD", envs);
	if (ft_strncmp(command, "cd .", 5) == 0)
	{
		ft_setenv("OLDPWD", pwd, envs);
		free(pwd);
	}
	else
	{
		if (command[2] == '\0')
			new_path = ft_getenv("HOME", envs);
		else
			new_path = ft_strdup(command + 3);
		g_exit_status = change_pwds(pwd, envs, new_path);
		free(new_path);
	}
	redo_envs(envs);
	return (g_exit_status);
}
