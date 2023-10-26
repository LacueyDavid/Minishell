/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 08:05:12 by jdenis            #+#    #+#             */
/*   Updated: 2023/10/03 18:37:51 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <cgreen/cgreen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Définition du fichier de sortie par défaut
const char	*default_output_file = "test.txt";

// Fonction de restauration de la sortie stdout
void	restore_stdout(const char *output_file)
{
	fclose(stdout);
	stdout = fopen(output_file, "w");
}

// Fonction de test
Describe(ft_pwd);
BeforeEach(ft_pwd)
{
	// Redirige stdout vers un fichier temporaire
	freopen("test.txt", "w", stdout);
}

AfterEach(ft_pwd)
{
	// Rétablit la sortie stdout normale
	restore_stdout(default_output_file);
}

Ensure(ft_pwd, classic)
{
	const char	*output_file;
	char		**input;
	int			output;
	FILE		*file;
	char		buffer[1024];

	output_file = "test1.txt";
	freopen(output_file, "w", stdout);
	//GIVEN (etant donné etat initial)
	input = NULL;
	//WHEN (quand)
	output = ft_pwd(input);
	fclose(stdout);
	// Ouvre le fichier temporaire pour lire la sortie stdout capturée
	file = fopen("test1.txt", "r");
	fgets(buffer, sizeof(buffer), file);
	// Vérifie que la sortie contient le texte attendu
	assert_that(buffer,
			is_equal_to_string("/mnt/nfs/homes/jdenis/Desktop/Cursus/Minishell/sources/minishell/builtins"));
	assert_that(output, is_equal_to(1));
	fclose(file);
	// Rétablit la sortie stdout normale avec le fichier par défaut
	restore_stdout(default_output_file);
}

Ensure(ft_pwd, error)
{
	const char	*output_file;
	char		*input[5];
	int			output;
	FILE		*file;
	char		buffer[1024];

	output_file = "test2.txt";
	freopen(output_file, "w", stdout);
	*input = "test";
	output = ft_pwd(input);
	fclose(stdout);
	file = fopen("test2.txt", "r");
	fgets(buffer, sizeof(buffer), file);
	assert_that(buffer, is_equal_to_string("pwd: too many arguments"));
	assert_that(output, is_equal_to(-1));
	fclose(file);
	restore_stdout(default_output_file);
}
