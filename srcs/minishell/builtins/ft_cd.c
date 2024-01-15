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
#include "builtins.h"

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
            free(envs->env[index]);
            envs->env[index] = malloc(sizeof(char) * (length + ft_strlen(value) + 2));
            strcpy(envs->env[index], name);
            strcat(envs->env[index], "=");
            strcat(envs->env[index], value);
            return ;
        }
        index++;
    }
}

void    change_pwd_in_env(char *path, t_envs *envs)
{
    char    *current_pwd;

    current_pwd = ft_getenv("PWD", envs);
    ft_setenv("OLDPWD", current_pwd, envs);
    ft_setenv("PWD", path, envs);
    free(current_pwd);
}

int ft_do_cd(t_envs *envs, char *command) 
{
    char *path;
    char *home_dir;
    char *new_path;

    path = ft_strdup(command + 3);
    if (path[0] != '~') 
        home_dir = ft_getenv("PWD", envs);
    else
        home_dir = ft_getenv("HOME", envs);
    if (home_dir != NULL) 
    {
        new_path = malloc(ft_strlen(home_dir) + ft_strlen(path) + 2);
        ft_strlcpy(new_path, home_dir, ft_strlen(home_dir) + 1); //utilise les ft
        ft_strlcat(new_path, "/", ft_strlen(new_path) + 2); //utilise les ft
        ft_strlcat(new_path, path, ft_strlen(new_path) + ft_strlen(path)); //utilise les ft
        free(path);
        free(home_dir);
    }
    else
    {
        perror("cd");
        free(path);
    }
    if (access(new_path, F_OK) == -1) 
    {
        perror("cd");
        free(new_path);
        return (EXIT_FAILURE);
    }
    change_pwd_in_env(new_path, envs);
    free(new_path);
    return (EXIT_SUCCESS);
}

int ft_cd(t_envs *envs, char *command)
{
    int exit_status;
    char *pwd;
    
    exit_status = EXIT_SUCCESS;
    pwd = ft_getenv("PWD", envs);
    if (ft_strncmp(command, "cd .", 5) == 0)
        ft_setenv("OLDPWD", pwd, envs);
    else if (ft_strncmp(command, "cd ...", 7) == 0)
        printf("cd: No such file or directory\n");
    else if (ft_strncmp(command, "cd ..",6) == 0)
    {
        free(pwd);
        pwd = getcwd(NULL, 0);
        chdir("..");
        ft_setenv("OLDPWD", pwd, envs);
        ft_setenv("PWD", pwd, envs);
    }
    else
        exit_status = ft_do_cd(envs, command);
    redo_envs(envs);
    free(pwd);
    return (exit_status);
}
