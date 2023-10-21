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
	node->values = malloc(sizeof(char *) * 3);
	node->values[0] = ft_strdup("echo");
	node->values[1] = ft_strdup("toto");
	node->values[2] = NULL;
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

	free_strs(node->values);
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
	node->values = malloc(sizeof(char *) * 4);
	node->values[0] = ft_strdup("echo");
	node->values[1] = ft_strdup("-n");
	node->values[2] = ft_strdup("toto");
	node->values[3] = NULL;
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

	free_strs(node->values);
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
	left->values = malloc(sizeof(char *) * 4);
	left->values[0] = ft_strdup("echo");
	left->values[1] = ft_strdup("-n");
	left->values[2] = ft_strdup("toto");
	left->values[3] = NULL;

	t_node *right = malloc(sizeof(t_node));
	right->type = SIMPLE_COMMAND;
	right->values = malloc(sizeof(char *) * 2);
	right->values[0] = ft_strdup(output_file);
	right->values[1] = NULL;

	t_node *head = malloc(sizeof(t_node));
	head->type = O_REDIRECTION;
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

	free_strs(left->values);
	free(left);
	free_strs(right->values);
	free(right);
	free(head);
	free(line);
}
