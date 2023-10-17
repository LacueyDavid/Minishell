
#include <cgreen/cgreen.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "unistd.h"
#include "fcntl.h"
#include "execution.h"

Describe(exec_full_command);

BeforeEach(exec_full_command) {}

AfterEach(exec_full_command) {}

Ensure(parse_full_command, can_parse_echo_toto)
{
	//GIVEN (etant donné etat initial)
	t_token_list *token_list = init_token_list();
	t_token token1;
	t_token token2;
	token1.type = WORD;
	token1.value = "echo";
	token2.type = WORD;
	token2.value = "toto";
	add_token(token_list, token1);
	add_token(token_list, token2);

	t_node *output = NULL;

	//WHEN (quand)
	output = parsing(token_list);

	//THEN (alors)
	assert_that(output->type, is_equal_to(SIMPLE_COMMAND));
	assert_that(output->value, is_equal_to_string("echo toto"));
	assert_that(output->left, is_equal_to(NULL));
	assert_that(output->right, is_equal_to(NULL));
}
