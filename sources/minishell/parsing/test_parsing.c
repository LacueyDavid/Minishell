
#include <cgreen/cgreen.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "unistd.h"
#include "fcntl.h"
#include "execution.h"
#include "parsing.h"
#include "libft.h"

Describe(parse_full_command);

BeforeEach(parse_full_command) {}

AfterEach(parse_full_command) {}

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

	t_node *head = NULL;

	//WHEN (quand)
	head = parsing(token_list);

	//THEN (alors)
	assert_that(head->type, is_equal_to(SIMPLE_COMMAND));
	assert_that(head->value[0], is_equal_to_string("echo"));
	assert_that(head->value[1], is_equal_to_string("toto"));
	assert_that(head->left, is_equal_to(NULL));
	assert_that(head->right, is_equal_to(NULL));

	free_strs(head->value);
}

Ensure(parse_full_command, can_parse_echo_toto_with_redirection)
{
	//GIVEN (etant donné etat initial)
	t_token_list *token_list = init_token_list();
	t_token token1;
	t_token token2;
	t_token token3;
	t_token token4;
	token1.type = WORD;
	token1.value = "echo";
	token2.type = WORD;
	token2.value = "toto";
	token3.type = O_REDIRECTION;
	token3.value = ">";
	token4.type = WORD;
	token4.value = "output.txt";
	add_token(token_list, token1);
	add_token(token_list, token2);
	add_token(token_list, token3);
	add_token(token_list, token4);

	t_node *head = NULL;

	//WHEN (quand)
	head = parsing(token_list);

	//THEN (alors)
	t_node *left = head->left;
	t_node *right = head->right;

	assert_that(head->type, is_equal_to(O_REDIRECTION));

	assert_that(left->type, is_equal_to(SIMPLE_COMMAND));
	assert_that(left->value[0], is_equal_to_string("echo"));
	assert_that(left->value[1], is_equal_to_string("toto"));
	assert_that(left->value[2], is_equal_to_string(NULL));
	assert_that(left->left, is_equal_to(NULL));
	assert_that(left->right, is_equal_to(NULL));

	assert_that(right->type, is_equal_to(O_REDIRECTION));
	assert_that(right->value[0], is_equal_to_string("output.txt"));
	assert_that(right->value[1], is_equal_to_string(NULL));
	assert_that(right->left, is_equal_to(NULL));
	assert_that(right->right, is_equal_to(NULL));

	free_strs(head->value);
}