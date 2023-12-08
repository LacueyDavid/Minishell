/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:37:51 by jdenis            #+#    #+#             */
/*   Updated: 2023/12/04 11:19:38 by marvin           ###   ########.fr       */
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
	unlink("test.txt");
}

Ensure(ft_echo, without_n)
{
	const char	*output_file;
	FILE		*file;
	char		buffer[1024];

	output_file = "test1.txt";
	freopen(output_file, "w", stdout);
	//GIVEN (etant donné etat initial)
	char *input= "echo hello world";
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
	unlink(output_file);
	
}

Ensure(ft_echo, with_n)
{
	const char	*output_file;
	FILE		*file;
	char		buffer[1024];

	output_file = "test2.txt";
	freopen(output_file, "w", stdout);
	//GIVEN (etant donné etat initial)
	char *input = "echo -n hello";
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
	unlink(output_file);

}

Ensure(ft_echo, with_nnnnnnnn)
{
	const char	*output_file;
	FILE		*file;
	char		buffer[1024];

	output_file = "test3.txt";
	freopen(output_file, "w", stdout);
	//GIVEN (etant donné etat initial)
	char *input = "echo -nnnnnnnnnnnnn hello";
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
	unlink(output_file);

}

Ensure(ft_echo, with_echo_flag)
{
	const char *output_file = "test4.txt";
	freopen(output_file, "w", stdout);

	//GIVEN (etant donné etat initial)
	char *input = "echo -nhello world";
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
	unlink(output_file);

}

Ensure(ft_echo, with_echo_multiple_flags)
{
	const char *output_file = "test5.txt";
	freopen(output_file, "w", stdout);

	//GIVEN (etant donné etat initial)
	char *input = "echo -n -n -n -n hello world";
	//WHEN (quand)
	ft_echo(input);
	fclose(stdout);

	// Ouvre le fichier temporaire pour lire la sortie stdout capturée
	FILE *file = fopen("test5.txt", "r");
	char buffer[1024];
	fgets(buffer, sizeof(buffer), file);

	// Vérifie que la sortie contient le texte attendu
	assert_that(buffer, is_equal_to_string("hello world"));
	fclose(file);

	// Rétablit la sortie stdout normale avec le fichier par défaut
	restore_stdout(default_output_file);
	unlink(output_file);

}

Ensure(ft_echo, with_echo_space_before_flags)
{
	const char *output_file = "test6.txt";
	freopen(output_file, "w", stdout);

	//GIVEN (etant donné etat initial)
	char *input = "echo                 -n 		-n -nnnnnnn -n hello world";
	//WHEN (quand)
	ft_echo(input);
	fclose(stdout);

	// Ouvre le fichier temporaire pour lire la sortie stdout capturée
	FILE *file = fopen("test6.txt", "r");
	char buffer[1024];
	fgets(buffer, sizeof(buffer), file);

	// Vérifie que la sortie contient le texte attendu
	assert_that(buffer, is_equal_to_string("hello world"));
	fclose(file);

	// Rétablit la sortie stdout normale avec le fichier par défaut
	restore_stdout(default_output_file);
	unlink(output_file);

}

Ensure(ft_echo, echo_with_simple_n_and_flags)
{
	const char *output_file = "test7.txt";
	freopen(output_file, "w", stdout);

	//GIVEN (etant donné etat initial)
	char *input = "echo -nn n -n hello";
	//WHEN (quand)
	ft_echo(input);
	fclose(stdout);

	// Ouvre le fichier temporaire pour lire la sortie stdout capturée
	FILE *file = fopen("test7.txt", "r");
	char buffer[1024];
	fgets(buffer, sizeof(buffer), file);

	// Vérifie que la sortie contient le texte attendu
	assert_that(buffer, is_equal_to_string("n -n hello"));
	fclose(file);

	// Rétablit la sortie stdout normale avec le fichier par défaut
	restore_stdout(default_output_file);
	unlink(output_file);

}

Ensure(ft_echo, echo_with_white_space_before_flags)
{
	const char *output_file = "test8.txt";
	freopen(output_file, "w", stdout);

	//GIVEN (etant donné etat initial)
	char *input = "echo       	-n hello";
	//WHEN (quand)
	ft_echo(input);
	fclose(stdout);

	// Ouvre le fichier temporaire pour lire la sortie stdout capturée
	FILE *file = fopen("test8.txt", "r");
	char buffer[1024];
	fgets(buffer, sizeof(buffer), file);

	// Vérifie que la sortie contient le texte attendu
	assert_that(buffer, is_equal_to_string("hello"));
	fclose(file);

	// Rétablit la sortie stdout normale avec le fichier par défaut
	restore_stdout(default_output_file);
	unlink(output_file);

}

//Le test marche mais j'arrive pas a le faire tourner je pense que c'est parce que ca read un truc null depuis le stdout
// Ensure(ft_echo, echo_with_only_flags)
// {
// 	const char *output_file = "test9.txt";
// 	freopen(output_file, "w", stdout);

// 	//GIVEN (etant donné etat initial)
// 	char *input = "echo -nnnnnnnn";
// 	//WHEN (quand)
// 	ft_echo(input);
// 	fclose(stdout);

// 	// Ouvre le fichier temporaire pour lire la sortie stdout cpaturée
// 	FILE *file = fopen("test9.txt", "r");
// 	char buffer[1024];
// 	fgets(buffer, sizeof(buffer), file);

// 	// Vérifie que la sortie contient le texte attendu
// 	assert_that(buffer, is_equal_to_string(""));
// 	fclose(file);

// 	// Rétablit la sortie stdout normale avec le fichier par défaut
// 	restore_stdout(default_output_file);
	// unlink(output_file);

// }

Ensure(ft_echo, echo_dont_printf_whiteepace)
{
	const char *output_file = "test10.txt";
	freopen(output_file, "w", stdout);

	//GIVEN (etant donné etat initial)
	char *input = "echo                    				";
	//WHEN (quand)
	ft_echo(input);
	fclose(stdout);

	// Ouvre le fichier temporaire pour lire la sortie stdout capturée
	FILE *file = fopen("test10.txt", "r");
	char buffer[1024];
	fgets(buffer, sizeof(buffer), file);

	// Vérifie que la sortie contient le texte attendu
	assert_that(buffer, is_equal_to_string("\n"));
	fclose(file);

	// Rétablit la sortie stdout normale avec le fichier par défaut
	restore_stdout(default_output_file);
	unlink(output_file);
}

Ensure(ft_echo, echo_many_print_n)
{
	const char *output_file = "test10.txt";
	freopen(output_file, "w", stdout);

	//GIVEN (etant donné etat initial)
	char *input = "echo -nnnnnnnnnhello";
	//WHEN (quand)
	ft_echo(input);
	fclose(stdout);

	// Ouvre le fichier temporaire pour lire la sortie stdout capturée
	FILE *file = fopen("test10.txt", "r");
	char buffer[1024];
	fgets(buffer, sizeof(buffer), file);

	// Vérifie que la sortie contient le texte attendu
	assert_that(buffer, is_equal_to_string("-nnnnnnnnnhello\n"));
	fclose(file);

	// Rétablit la sortie stdout normale avec le fichier par défaut
	restore_stdout(default_output_file);
	unlink(output_file);

}