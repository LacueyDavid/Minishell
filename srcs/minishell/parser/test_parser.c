/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 05:28:31 by dlacuey           #+#    #+#             */
/*   Updated: 2023/11/23 05:35:55 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cgreen/cgreen.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "unistd.h"
#include "fcntl.h"
#include "execution.h"
#include "parser.h"
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
	token1.value = ft_strdup("echo");
	token2.type = WORD;
	token2.value = ft_strdup("toto");
	add_token(token_list, token1);
	add_token(token_list, token2);

	t_node *head = NULL;

	//WHEN (quand)
	head = parser(token_list);

	//THEN (alors)
	assert_that(head->type, is_equal_to(SIMPLE_COMMAND));
	assert_that(head->vector_strs.values[0], is_equal_to_string("echo"));
	assert_that(head->vector_strs.values[1], is_equal_to_string("toto"));
	assert_that(head->left, is_equal_to(NULL));
	assert_that(head->right, is_equal_to(NULL));

	destroy_token_list(token_list);
	clear_tree(head);
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
	token1.value = ft_strdup("echo");
	token2.type = WORD;
	token2.value = ft_strdup("toto");
	token3.type = O_REDIRECTION;
	token3.value = ft_strdup(">");
	token4.type = WORD;
	token4.value = ft_strdup("output.txt");
	add_token(token_list, token1);
	add_token(token_list, token2);
	add_token(token_list, token3);
	add_token(token_list, token4);

	t_node *head = NULL;

	//WHEN (quand)
	head = parser(token_list);

	//THEN (alors)
	t_node *left = head->left;
	t_node *right = head->right;

	assert_that(head->type, is_equal_to(COMMAND_O_REDIRECT));

	assert_that(left->type, is_equal_to(SIMPLE_COMMAND));
	assert_that(left->vector_strs.values[0], is_equal_to_string("echo"));
	assert_that(left->vector_strs.values[1], is_equal_to_string("toto"));
	assert_that(left->vector_strs.values[2], is_equal_to_string(NULL));
	assert_that(left->left, is_equal_to(NULL));
	assert_that(left->right, is_equal_to(NULL));

	assert_that(right->vector_strs.values[0], is_equal_to_string("output.txt"));
	assert_that(right->vector_strs.values[1], is_equal_to_string(NULL));
	assert_that(right->left, is_equal_to(NULL));
	assert_that(right->right, is_equal_to(NULL));

	clear_tree(head);
	destroy_token_list(token_list);
}

Ensure(parse_full_command, can_parse_simple_pipe)
{
	//GIVEN (etant donné etat initial)
	t_token_list *token_list = init_token_list();
	t_token token1;
	t_token token2;
	t_token token3;
	t_token token4;
	t_token token5;
	token1.type = WORD;
	token1.value = ft_strdup("echo");
	token2.type = WORD;
	token2.value = ft_strdup("toto");
	token3.type = PIPE;
	token3.value = ft_strdup("|");
	token4.type = WORD;
	token4.value = ft_strdup("wc");
	token5.type = WORD;
	token5.value = ft_strdup("-l");
	add_token(token_list, token1);
	add_token(token_list, token2);
	add_token(token_list, token3);
	add_token(token_list, token4);
	add_token(token_list, token5);

	t_node *head = NULL;

	//WHEN (quand)
	head = parser(token_list);

	//THEN (alors)
	t_node *left = head->left;
	t_node *right = head->right;

	assert_that(head->type, is_equal_to(COMMAND_PIPE));
	assert_that(left->type, is_equal_to(SIMPLE_COMMAND));
	assert_that(left->vector_strs.values[0], is_equal_to_string("echo"));
	assert_that(left->vector_strs.values[1], is_equal_to_string("toto"));
	assert_that(left->vector_strs.values[2], is_equal_to_string(NULL));
	assert_that(left->left, is_equal_to(NULL));
	assert_that(left->right, is_equal_to(NULL));
	assert_that(right->type, is_equal_to(SIMPLE_COMMAND));
	assert_that(right->vector_strs.values[0], is_equal_to_string("wc"));
	assert_that(right->vector_strs.values[1], is_equal_to_string("-l"));
	assert_that(right->vector_strs.values[2], is_equal_to_string(NULL));
	assert_that(right->left, is_equal_to(NULL));
	assert_that(right->right, is_equal_to(NULL));

	clear_tree(head);
	destroy_token_list(token_list);
}
