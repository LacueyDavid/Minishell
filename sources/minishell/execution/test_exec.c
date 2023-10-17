#include <cgreen/cgreen.h>
#include <stdlib.h>
#include <string.h>
#include "execution.h"
#include "unistd.h"

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

Ensure(exec_full_command, a_simple_command)
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

    assert_that(buffer, is_equal_to_string("toto\n"));
    fclose(file);
	free(node);
	unlink(output_file);

    restore_stdout(default_output_file);
}
