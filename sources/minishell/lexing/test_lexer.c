#include <cgreen/cgreen.h>
#include "lexer.h"

Describe(lexer);
BeforeEach(lexer) {}
AfterEach(lexer) {}

Ensure(lexer, recognizes_a_word)
{
	//GIVEN (etant donné etat initial)
	char *input = "hello";
	t_token_list *token_list = NULL;
	//WHEN (quand)
	token_list = lexer(input);
	//THEN (alors)
	assert_that(token_list->size, is_equal_to(1));
	assert_that(token_list->tokens[0].type, is_equal_to(WORD));
	assert_that(token_list->tokens[0].value, is_equal_to_string("hello"));
	destroy_token_list(token_list);
}

Ensure(lexer, recognizes_multiple_tokens)
{
	//GIVEN
	char *input = "hello world!";
	t_token_list *token_list = NULL;
	//WHEN
	token_list = lexer(input);
	//THEN
	assert_that(token_list->size, is_equal_to(2));
	assert_that(token_list->tokens[0].type, is_equal_to(WORD));
	assert_that(token_list->tokens[0].value, is_equal_to_string("hello"));
	assert_that(token_list->tokens[1].type, is_equal_to(WORD));
	assert_that(token_list->tokens[1].value, is_equal_to_string("world!"));
	destroy_token_list(token_list);
}
