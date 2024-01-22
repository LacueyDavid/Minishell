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

char	*create_new_path(char *path, char *home_dir)
{
	char	*new_path;

	new_path = malloc(ft_strlen(home_dir) + ft_strlen(path) + 2);
	ft_strlcpy(new_path, home_dir, ft_strlen(home_dir) + 1);
	ft_strlcat(new_path, "/", ft_strlen(new_path) + 2);
	ft_strlcat(new_path, path, ft_strlen(new_path) + ft_strlen(path));
	free(path);
	free(home_dir);
	return (new_path);
}

char	*ft_strdup_end(char *str, int start)
{
	char	*new;
	int		index;

	index = start;
	new = malloc(ft_strlen(str) - start + 1);
	if (!new)
		return (NULL);
	while (str[index])
	{
		new[index - start] = str[index];
		index++;
	}
	new[index - start] = '\0';
	free(str);
	return (new);
}

int	error_access(char *new_path)
{
	perror("cd");
	free(new_path);
	return (EXIT_FAILURE);
}

int	ft_do_cd(t_envs *envs, char *command)
{
	char	*path;
	char	*home_dir;
	char	*new_path;

	path = ft_strdup(command + 3);
	if (path[0] != '~')
		home_dir = ft_getenv("PWD", envs);
	else
	{
		home_dir = ft_getenv("HOME", envs);
		path = ft_strdup_end(path, 2);
	}
	if (home_dir != NULL)
		new_path = create_new_path(path, home_dir);
	else
	{
		perror("cd");
		free(path);
	}
	if (access(new_path, F_OK) == -1)
		return (error_access(new_path));
	change_pwd_in_env(new_path, envs);
	free(new_path);
	return (EXIT_SUCCESS);
}

int	ft_cd(t_envs *envs, char *command)
{
	int		g_exit_status;
	char	*pwd;

	g_exit_status = EXIT_SUCCESS;
	pwd = ft_getenv("PWD", envs);
	if (ft_strncmp(command, "cd .", 5) == 0)
		ft_setenv("OLDPWD", pwd, envs);
	else if (ft_strncmp(command, "cd ...", 7) == 0)
		printf("cd: No such file or directory\n");
	else if (ft_strncmp(command, "cd ..", 6) == 0)
	{
		free(pwd);
		chdir("..");
		pwd = getcwd(NULL, 0);
		ft_setenv("OLDPWD", pwd, envs);
		ft_setenv("PWD", pwd, envs);
	}
	else
		g_exit_status = ft_do_cd(envs, command);
	redo_envs(envs);
	free(pwd);
	return (g_exit_status);
}
