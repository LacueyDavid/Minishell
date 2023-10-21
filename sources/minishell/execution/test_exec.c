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
	node->value[0] = ft_strdup("echo");
	node->value[1] = ft_strdup("toto");
	node->value[2] = NULL;
	node->left = NULL;
	node->right = NULL;
	//WHEN (quand)
	// int fd = open(output_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	// dup2(fd, STDOUT_FILENO);
	FILE *file = fopen(output_file, "w");
	freopen(output_file, "w", stdout);
	exec_full_command(node);

	//THEN (alors)
	int fd = open(output_file, O_RDONLY);
	line = get_next_line(fd);
	assert_that(line, is_equal_to_string("toto\n"));
	close(fd);
	unlink(output_file);

	free_strs(node->value);
	free(node);
	free(line);
	fclose(file);
}

Ensure(exec_full_command, can_exec_echo_toto_with_option)
{
	const char *output_file = "test.txt";
	char *line;

	//GIVEN (etant donné etat initial)
	t_node *node = malloc(sizeof(t_node));
	node->type = SIMPLE_COMMAND;
	node->value = malloc(sizeof(char *) * 4);
	node->value[0] = ft_strdup("echo");
	node->value[1] = ft_strdup("-n");
	node->value[2] = ft_strdup("toto");
	node->value[3] = NULL;
	node->left = NULL;
	node->right = NULL;
	//WHEN (quand)
	// int fd = open(output_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	// dup2(fd, STDOUT_FILENO);
	FILE *file = fopen(output_file, "w");
	freopen(output_file, "w", stdout);
	exec_full_command(node);

	//THEN (alors)
	int fd = open(output_file, O_RDONLY);
	line = get_next_line(fd);
	assert_that(line, is_equal_to_string("toto"));
	close(fd);
	unlink(output_file);

	free_strs(node->value);
	free(node);
	free(line);
	fclose(file);
}

Ensure(exec_full_command, can_exec_echo_toto_with_redirection)
{
	const char *output_file = "outfile.txt";
	char *line;

	//GIVEN (etant donné etat initial)
	t_node *left = malloc(sizeof(t_node));
	left->type = SIMPLE_COMMAND;
	left->value = malloc(sizeof(char *) * 4);
	left->value[0] = ft_strdup("echo");
	left->value[1] = ft_strdup("-n");
	left->value[2] = ft_strdup("toto");
	left->value[3] = NULL;

	t_node *right = malloc(sizeof(t_node));
	right->type = SIMPLE_COMMAND;
	right->value = malloc(sizeof(char *) * 2);
	right->value[0] = ft_strdup(output_file);
	right->value[1] = NULL;

	t_node *head = malloc(sizeof(t_node));
	head->type = O_REDIRECTION;
	head->left = left;
	head->right = right;

	//WHEN (quand)
	exec_full_command(head);

	//THEN (alors)
	int fd = open(output_file, O_RDONLY);
	line = get_next_line(fd);
	assert_that(line, is_equal_to_string("toto"));
	close(fd);
	unlink(output_file);

	free_strs(left->value);
	free(left);
	free_strs(right->value);
	free(right);
	free(head);
	free(line);
}
