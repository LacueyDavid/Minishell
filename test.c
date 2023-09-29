#include "sources/minishell/lexing/lexer.h"
#include <stdio.h>

int main(void)
{
	char *input = "hello world!";
	t_token_list *token_list = lexer(input);
	printf("token_list->size = %ld\n", token_list->size);
	printf("token_list->tokens[0].type = %d\n", token_list->tokens[0].type);
	printf("token_list->tokens[0].value = %s\n", token_list->tokens[0].value);
	printf("token_list->tokens[1].type = %d\n", token_list->tokens[1].type);
	printf("token_list->tokens[1].value = %s\n", token_list->tokens[1].value);
	return (0);
}


