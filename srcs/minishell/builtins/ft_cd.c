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
#include "libft.h"

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
