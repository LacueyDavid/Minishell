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

int ft_cd(char *command) 
{
    // char *path;

    // // Ignorer la commande "cd" et extraire le chemin
    // if (strncmp(command, "cd ", 3) == 0) 
	// {
    //     path = strdup(command + 3); // Ignorer les trois premiers caractères (cd )

    //     // Traiter le cas de ~ pour le répertoire personnel
    //     if (path[0] == '~') 
	// 	{
    //         const char *home_dir = getenv("HOME");
    //         if (home_dir != NULL) 
	// 		{
    //             printf("Changement vers le répertoire personnel : %s\n", home_dir);

    //             char *new_path = malloc(strlen(home_dir) + strlen(path));
    //             strcpy(new_path, home_dir);
    //             strcat(new_path, path + 1); // Ignorer le ~
    //             free(path);
    //             path = new_path;
    //         }
    //     }

    //     printf("Changement de répertoire vers : %s\n", path);

    //     // Utiliser chdir pour changer de répertoire
    //     if (chdir(path) != 0) 
	// 	{
    //         perror("ft_cd");
    //     }

    //     free(path);
    // } 
	// else 
	// {
    //     fprintf(stderr, "Commande cd non valide : %s\n", command);
    // }
}

int main(void) 
{
	chdir("/home/jdenis/");
	// ft_cd("cd ..");
	// ft_cd("cd /tmp");
	// ft_cd("cd ~");
	// ft_cd("cd ~/Documents");
}