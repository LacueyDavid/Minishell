/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:37:33 by marvin            #+#    #+#             */
/*   Updated: 2023/12/04 11:37:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "environnement.h"
#include "libft.h"

void    change_pwd(char *path)
{
    char *pwd;
    char *oldpwd;

    pwd = malloc(sizeof(char) * 1024);
    oldpwd = malloc(sizeof(char) * 1024);
    pwd = getcwd(pwd, 1024);
    oldpwd = getenv("OLDPWD");
    setenv("OLDPWD", pwd, 1);
    setenv("PWD", path, 1);
    free(pwd);
    free(oldpwd);
}

char    *ft_getenv(char *name, t_envs *envs)
{
    size_t  index;
    size_t  length;
    char    *value;

    index = 0;
    length = ft_strlen(name);
    while (envs->env[index])
    {
        if (!ft_strncmp(envs->env[index], name, length))
        {
            value = ft_strdup(envs->env[index] + length + 1);
            return (value);
        }
        index++;
    }
    return (NULL);
}

void    ft_setenv(char *name, char *value, t_envs *envs)
{
    size_t  index;
    size_t  length;

    index = 0;
    length = ft_strlen(name);
    while (envs->env[index])
    {
        if (ft_strncmp(envs->env[index], name, length) == 0)
        {
            envs->env[index] = ft_realloc(envs->env[index], length + ft_strlen(value) + 1, ft_strelen(envs->env[index]));
            envs->env[index] = ft_strcat(envs->env[index], value);
        }
        index++;
    }
}

void    change_pwd(char *path, t_envs *envs)
{
    ft_setenv("OLDPWD", ft_getenv("PWD", envs), envs);
    ft_setenv("PWD", path, envs);
}

int ft_cd(char *command) 
{
    char *path;
    char *home_dir;
    char *new_path;

    path = ft_strdup(command + 3);
    if (path[0] == '~') 
    {
        home_dir = malloc(ft_strlen(path) + ft_strlen(getenv("HOME")));
        home_dir = getenv("HOME");
        if (home_dir != NULL) 
        {
            new_path = malloc(ft_strlen(home_dir) + ft_strlen(path));
            strcpy(new_path, home_dir); //utilise les ft
            strcat(new_path, path + 1); //utilise les ft
            free(path);
            path = new_path;
            free(new_path);
            free(home_dir);
        }
    }
    if (chdir(path) != 0) 
    {
        perror("cd");
        return (EXIT_FAILURE);
    }
    free(path);
    return (EXIT_SUCCESS);
}
