#include <cgreen/cgreen.h>
#include <stdlib.h>
#include <string.h>
#include "execution.h"
#include "unistd.h"
#include "fcntl.h"
#include "get_next_line.h"
#include "libft.h"

Describe(exec_full_command);

BeforeEach(exec_full_command) {}

AfterEach(exec_full_command) {}

Ensure(exec_full_command, can_exec_echo_toto)
{
	const char *output_file = "test.txt";
	char *line;

	//GIVEN (etant donné etat initial)
	t_node *node = malloc(sizeof(t_node));
	node->type = SIMPLE_COMMAND;
	node->value = malloc(sizeof(char *) * 3);
	node->value[0] = "echo";
	node->value[1] = "toto";
	node->value[2] = NULL;
	node->left = NULL;
	node->right = NULL;
	//WHEN (quand)
	int fd = open(output_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	dup2(fd, STDOUT_FILENO);
	exec_full_command(node);

	//THEN (alors
	line = get_next_line(fd);
	assert_that(line, is_equal_to_string("toto\n"));
	close(fd);
	unlink(output_file);

	free_strs(node->value);
	free(node);
	free(line);
}
//
// Ensure(exec_full_command, exec_echo_toto_with_option)
// {
//     const char *output_file = "test.txt";
//     freopen(output_file, "w", stdout);
//
//     //GIVEN (etant donné etat initial)
//     t_node *node = malloc(sizeof(t_node));
// 	node->type = SIMPLE_COMMAND;
// 	node->value = malloc(sizeof(char *) * 4);
// 	node->value[0] = "echo";
// 	node->value[1] = "-n";
// 	node->value[2] = "toto";
// 	node->value[3] = NULL;
// 	node->left = NULL;
// 	node->right = NULL;
//     //WHEN (quand)
//     exec_full_command(node);
//     fclose(stdout);
//
//     FILE *file = fopen("test.txt", "r");
//     char buffer[1024];
//     fgets(buffer, sizeof(buffer), file);
//
// 	//THEN (alors)
//     assert_that(buffer, is_equal_to_string("toto"));
//     fclose(file);
// 	unlink(output_file);
//
// 	free_strs(node->value);
// 	free(node);
//     restore_stdout(default_output_file);
// }
//
// Ensure(exec_full_command, exec_echo_toto_with_redirection)
// {
//     //GIVEN (etant donné etat initial)
// 	char *output_file = "output.txt";
//
// 	t_node *node_left = malloc(sizeof(t_node));
// 	node_left->type = SIMPLE_COMMAND;
// 	node_left->value = malloc(sizeof(char *) * 3);
// 	node_left->value[0] = "echo";
// 	node_left->value[1] = "toto";
// 	node_left->value[2] = NULL;
// 	node_left->left = NULL;
// 	node_left->right = NULL;
//
// 	t_node *node_right = malloc(sizeof(t_node));
// 	node_right->type = WORD;
// 	node_right->value = malloc(sizeof(char *) * 2);
// 	node_right->value[0] = output_file;
// 	node_right->value[1] = NULL;
// 	node_right->left = NULL;
// 	node_right->right = NULL;
//
//     t_node *node = malloc(sizeof(t_node));
// 	node->type = O_REDIRECTION;
// 	node->value = NULL;
// 	node->left = node_left;
// 	node->right = node_right;
//
//     //WHEN (quand)
//     exec_full_command(node);
// 	int fd = open(output_file, O_RDONLY);
// 	//THEN (alors)
// 	assert_that(get_next_line(fd), is_equal_to_string("toto\n"));
// 	unlink(output_file);
// 	close(fd);
// 	free_strs(node_left->value);
// 	free_strs(node_right->value);
// 	free(node);
// 	free(node_left);
// 	free(node_right);
// }
