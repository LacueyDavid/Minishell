#include <cgreen/cgreen.h>
#include <stdlib.h>
#include <string.h>
#include "execution.h"
#include "unistd.h"
#include "fcntl.h"
#include "get_next_line.h"
#include "libft.h"

Describe(execution);

BeforeEach(execution) {}

AfterEach(execution) {}

Ensure(execution, can_exec_echo_toto)
{
	const char *output_file = "test.txt";
	char *line;

	//GIVEN (etant donné etat initial)
	t_node *node = malloc(sizeof(t_node));
	node->type = SIMPLE_COMMAND;
	node->vector_strs.values = malloc(sizeof(char *) * 3);
	node->vector_strs.values[0] = ft_strdup("echo");
	node->vector_strs.values[1] = ft_strdup("toto");
	node->vector_strs.values[2] = NULL;
	node->left = NULL;
	node->right = NULL;
	//WHEN (quand)
	// int fd = open(output_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	// dup2(fd, STDOUT_FILENO);
	FILE *file = fopen(output_file, "w");
	freopen(output_file, "w", stdout);
	execution(node);

	//THEN (alors)
	int fd = open(output_file, O_RDONLY);
	line = get_next_line(fd);
	assert_that(line, is_equal_to_string("toto\n"));
	close(fd);
	unlink(output_file);

	free_strs(node->vector_strs.values);
	free(node);
	free(line);
	fclose(file);
}

Ensure(execution, can_exec_echo_toto_with_option)
{
	const char *output_file = "test.txt";
	char *line;

	//GIVEN (etant donné etat initial)
	t_node *node = malloc(sizeof(t_node));
	node->type = SIMPLE_COMMAND;
	node->vector_strs.values = malloc(sizeof(char *) * 4);
	node->vector_strs.values[0] = ft_strdup("echo");
	node->vector_strs.values[1] = ft_strdup("-n");
	node->vector_strs.values[2] = ft_strdup("toto");
	node->vector_strs.values[3] = NULL;
	node->left = NULL;
	node->right = NULL;
	//WHEN (quand)
	// int fd = open(output_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	// dup2(fd, STDOUT_FILENO);
	FILE *file = fopen(output_file, "w");
	freopen(output_file, "w", stdout);
	execution(node);

	//THEN (alors)
	int fd = open(output_file, O_RDONLY);
	line = get_next_line(fd);
	assert_that(line, is_equal_to_string("toto"));
	close(fd);
	unlink(output_file);

	free_strs(node->vector_strs.values);
	free(node);
	free(line);
	fclose(file);
}

Ensure(execution, can_exec_echo_toto_with_redirection)
{
	const char *output_file = "outfile.txt";
	char *line;

	//GIVEN (etant donné etat initial)
	t_node *left = malloc(sizeof(t_node));
	left->type = SIMPLE_COMMAND;
	left->vector_strs.values = malloc(sizeof(char *) * 4);
	left->vector_strs.values[0] = ft_strdup("echo");
	left->vector_strs.values[1] = ft_strdup("-n");
	left->vector_strs.values[2] = ft_strdup("toto");
	left->vector_strs.values[3] = NULL;

	t_node *right = malloc(sizeof(t_node));
	right->type = SIMPLE_COMMAND;
	right->vector_strs.values = malloc(sizeof(char *) * 2);
	right->vector_strs.values[0] = ft_strdup(output_file);
	right->vector_strs.values[1] = NULL;

	t_node *head = malloc(sizeof(t_node));
	head->type = COMMAND_O_REDIRECT;
	head->left = left;
	head->right = right;

	//WHEN (quand)
	execution(head);

	//THEN (alors)
	int fd = open(output_file, O_RDONLY);
	line = get_next_line(fd);
	assert_that(line, is_equal_to_string("toto"));
	close(fd);
	unlink(output_file);

	free_strs(left->vector_strs.values);
	free(left);
	free_strs(right->vector_strs.values);
	free(right);
	free(head);
	free(line);
}
