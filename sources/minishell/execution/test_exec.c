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
