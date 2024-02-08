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

int	change_pwds(char *pwd, t_envs *envs, char *new_path, bool pwd_exist)
{
	char	*tmp;

	if (chdir(new_path))
	{
		perror("cd");
		return (EXIT_FAILURE);
	}
	if (pwd_exist)
		ft_setenv("OLDPWD", pwd, envs);
	tmp = getcwd(NULL, 0);
	ft_setenv("PWD", tmp, envs);
	free(tmp);
	(free(new_path), free(pwd));
	return (EXIT_SUCCESS);
}

bool	remove_oldpwd(t_envs *envs, char *pwd)
{
	if (!pwd)
	{
		remove_environment_variable(envs->env, "OLDPWD");
		remove_environment_variable(envs->exports, "OLDPWD");
		return (false);
	}
	return (true);
}

char	*home_not_set(char *pwd, char *str)
{
	printf("%s", str);
	free(pwd);
	return (NULL);
}

char	*get_to_cd(char *command, t_envs *envs, char *pwd)
{
	char	*new_path;

	if (command[2] == '\0')
	{
		new_path = ft_getenv("HOME", envs);
		if (!new_path)
			return (home_not_set(pwd, "cd: HOME not set\n"));
	}
	else
	{
		new_path = ft_strdup(command + 3);
		if (!new_path)
			return (home_not_set(pwd, "malloc error\n"));
	}
	return (new_path);
}

int	ft_cd(t_envs *envs, char *command)
{
	int		g_exit_status;
	char	*pwd;
	char	*new_path;
	bool	pwd_exist;

	if (!envs->env)
		return (EXIT_FAILURE);
	g_exit_status = EXIT_SUCCESS;
	pwd = ft_getenv("PWD", envs);
	pwd_exist = remove_oldpwd(envs, pwd);
	if (!pwd_exist)
		pwd = getcwd(NULL, 0);
	if (ft_strncmp(command, "cd .", 5) == 0)
	{
		cd_point(pwd_exist, envs, pwd);
	}
	else
	{
		new_path = get_to_cd(command, envs, pwd);
		if (!new_path)
			return (EXIT_FAILURE);
		g_exit_status = change_pwds(pwd, envs, new_path, pwd_exist);
	}
	return (g_exit_status);
}
