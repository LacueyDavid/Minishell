/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:37:51 by jdenis            #+#    #+#             */
/*   Updated: 2023/10/03 18:37:47 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <cgreen/cgreen.h>
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
Describe(ft_echo);
BeforeEach(ft_echo)
{
	// Redirige stdout vers un fichier temporaire
	freopen("test.txt", "w", stdout);
}

AfterEach(ft_echo)
{
	// Rétablit la sortie stdout normale
	restore_stdout(default_output_file);
}

Ensure(ft_echo, without_n)
{
	const char	*output_file;
	char		*input[3];
	FILE		*file;
	char		buffer[1024];

	output_file = "test1.txt";
	freopen(output_file, "w", stdout);
	//GIVEN (etant donné etat initial)
	input[3] = {"hello", "world", 0};
	//WHEN (quand)
	ft_echo(input);
	fclose(stdout);
	// Ouvre le fichier temporaire pour lire la sortie stdout capturée
	file = fopen("test1.txt", "r");
	fgets(buffer, sizeof(buffer), file);
	// Vérifie que la sortie contient le texte attendu
	assert_that(buffer, is_equal_to_string("hello world\n"));
	fclose(file);
	// Rétablit la sortie stdout normale avec le fichier par défaut
	restore_stdout(default_output_file);
}

Ensure(ft_echo, with_n)
{
	const char	*output_file;
	char		*input[3];
	FILE		*file;
	char		buffer[1024];

	output_file = "test2.txt";
	freopen(output_file, "w", stdout);
	//GIVEN (etant donné etat initial)
	input[3] = {"-n", "hello", 0};
	//WHEN (quand)
	ft_echo(input);
	fclose(stdout);
	// Ouvre le fichier temporaire pour lire la sortie stdout capturée
	file = fopen("test2.txt", "r");
	fgets(buffer, sizeof(buffer), file);
	// Vérifie que la sortie contient le texte attendu
	assert_that(buffer, is_equal_to_string("hello"));
	fclose(file);
	// Rétablit la sortie stdout normale avec le fichier par défaut
	restore_stdout(default_output_file);
}

Ensure(ft_echo, with_nnnnnnnn)
{
	const char	*output_file;
	char		*input[3];
	FILE		*file;
	char		buffer[1024];

	output_file = "test3.txt";
	freopen(output_file, "w", stdout);
	//GIVEN (etant donné etat initial)
	input[3] = {"-nnnnnnnnnnnnn", "hello", 0};
	//WHEN (quand)
	ft_echo(input);
	fclose(stdout);
	// Ouvre le fichier temporaire pour lire la sortie stdout capturée
	file = fopen("test3.txt", "r");
	fgets(buffer, sizeof(buffer), file);
	// Vérifie que la sortie contient le texte attendu
	assert_that(buffer, is_equal_to_string("hello"));
	fclose(file);
	// Rétablit la sortie stdout normale avec le fichier par défaut
	restore_stdout(default_output_file);
}

Ensure(ft_echo, with_echo_flag)
{
	const char *output_file = "test4.txt";
	freopen(output_file, "w", stdout);

	//GIVEN (etant donné etat initial)
	char *input[3] = {"-nhello", "world", 0};
	//WHEN (quand)
	ft_echo(input);
	fclose(stdout);

	// Ouvre le fichier temporaire pour lire la sortie stdout capturée
	FILE *file = fopen("test4.txt", "r");
	char buffer[1024];
	fgets(buffer, sizeof(buffer), file);

	// Vérifie que la sortie contient le texte attendu
	assert_that(buffer, is_equal_to_string("-nhello world\n"));
	fclose(file);

	// Rétablit la sortie stdout normale avec le fichier par défaut
	restore_stdout(default_output_file);
}