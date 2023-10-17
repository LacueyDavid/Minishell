#include <cgreen/cgreen.h>
#include <stdlib.h>
#include <string.h>
#include "execution.h"
#include "unistd.h"
#include "fcntl.h"
#include "get_next_line.h"

const char *default_output_file = "test.txt";

void restore_stdout(const char	*output_file) {
    fclose(stdout);
    stdout = fopen(output_file, "w");
}

Describe(exec_full_command);

BeforeEach(exec_full_command)
{
    freopen("test.txt", "w", stdout);
}

AfterEach(exec_full_command)
{
	restore_stdout(default_output_file);
	unlink(default_output_file);
}

Ensure(exec_full_command, can_exec_echo_toto)
{
    const char *output_file = "test1.txt";
    freopen(output_file, "w", stdout);

    //GIVEN (etant donné etat initial)
    t_node *node = malloc(sizeof(t_node));
	node->type = SIMPLE_COMMAND;
	node->value = "echo toto";
	node->left = NULL;
	node->right = NULL;
    //WHEN (quand)
    exec_full_command(node);
    fclose(stdout);

    FILE *file = fopen("test1.txt", "r");
    char buffer[1024];
    fgets(buffer, sizeof(buffer), file);
	//THEN (alors
    assert_that(buffer, is_equal_to_string("toto\n"));
    fclose(file);
	free(node);
	unlink(output_file);

    restore_stdout(default_output_file);
}

Ensure(exec_full_command, exec_echo_toto_with_option)
{
    const char *output_file = "test1.txt";
    freopen(output_file, "w", stdout);

    //GIVEN (etant donné etat initial)
    t_node *node = malloc(sizeof(t_node));
	node->type = SIMPLE_COMMAND;
	node->value = "echo -n toto";
	node->left = NULL;
	node->right = NULL;
    //WHEN (quand)
    exec_full_command(node);
    fclose(stdout);

    FILE *file = fopen("test1.txt", "r");
    char buffer[1024];
    fgets(buffer, sizeof(buffer), file);

	//THEN (alors)
    assert_that(buffer, is_equal_to_string("toto"));
    fclose(file);
	free(node);
	unlink(output_file);

    restore_stdout(default_output_file);
}

Ensure(exec_full_command, exec_echo_toto_with_redirection)
{
    //GIVEN (etant donné etat initial)
	char *output_file = "output.txt";

	t_node *node_left = malloc(sizeof(t_node));
	node_left->type = SIMPLE_COMMAND;
	node_left->value = "echo toto";
	node_left->left = NULL;
	node_left->right = NULL;

	t_node *node_right = malloc(sizeof(t_node));
	node_right->type = WORD;
	node_right->value = output_file;
	node_right->left = NULL;
	node_right->right = NULL;

    t_node *node = malloc(sizeof(t_node));
	node->type = O_REDIRECTION;
	node->value = NULL;
	node->left = node_left;
	node->right = node_right;

    //WHEN (quand)
    exec_full_command(node);
	int fd = open(output_file, O_RDONLY);
	//THEN (alors)
	assert_that(get_next_line(fd), is_equal_to_string("toto\n"));
	unlink(output_file);
	close(fd);
	free(node);
	free(node_left);
	free(node_right);
}
