/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 05:28:31 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/07 13:09:04 by dlacuey          ###   ########.fr       */
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
	t_node *head = NULL;

	token1.type = WORD;
	token1.value = ft_strdup("echo");
	token2.type = WORD;
	token2.value = ft_strdup("toto");

	add_token(token_list, token1);
	add_token(token_list, token2);

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
	t_node *head = NULL;

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
	t_node *head = NULL;

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

Ensure(parse_full_command, can_parse_2_pipes)
{
	//GIVEN (etant donné etat initial)
	t_token_list *token_list = init_token_list();
	t_token token1;
	t_token token2;
	t_token token3;
	t_token token4;
	t_token token5;
	t_token token6;
	t_token token7;
	t_token token8;
	t_node *head = NULL;

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
	token6.type = PIPE;
	token6.value = ft_strdup("|");
	token7.type = WORD;
	token7.value = ft_strdup("tamere");
	token8.type = WORD;
	token8.value = ft_strdup("-d");

	add_token(token_list, token1);
	add_token(token_list, token2);
	add_token(token_list, token3);
	add_token(token_list, token4);
	add_token(token_list, token5);
	add_token(token_list, token6);
	add_token(token_list, token7);
	add_token(token_list, token8);

	//WHEN (quand)
	head = parser(token_list);

	//THEN (alors)
	t_node *left = head->left;
	t_node *right = head->right;
	t_node *right_left = head->right->left;
	t_node *right_right = head->right->right;

	assert_that(head->type, is_equal_to(COMMAND_PIPE));
	assert_that(left->type, is_equal_to(SIMPLE_COMMAND));
	assert_that(left->vector_strs.values[0], is_equal_to_string("echo"));
	assert_that(left->vector_strs.values[1], is_equal_to_string("toto"));
	assert_that(left->vector_strs.values[2], is_equal_to_string(NULL));
	assert_that(left->left, is_equal_to(NULL));
	assert_that(left->right, is_equal_to(NULL));
	assert_that(right->type, is_equal_to(COMMAND_PIPE));
	assert_that(right_left->type, is_equal_to(SIMPLE_COMMAND));
	assert_that(right_left->vector_strs.values[0], is_equal_to_string("wc"));
	assert_that(right_left->vector_strs.values[1], is_equal_to_string("-l"));
	assert_that(right_left->vector_strs.values[2], is_equal_to_string(NULL));
	assert_that(right_left->left, is_equal_to(NULL));
	assert_that(right_left->right, is_equal_to(NULL));
	assert_that(right_right->type, is_equal_to(SIMPLE_COMMAND));
	assert_that(right_right->vector_strs.values[0], is_equal_to_string("tamere"));
	assert_that(right_right->vector_strs.values[1], is_equal_to_string("-d"));
	assert_that(right_right->vector_strs.values[2], is_equal_to_string(NULL));
	assert_that(right_right->left, is_equal_to(NULL));
	assert_that(right_right->right, is_equal_to(NULL));

	clear_tree(head);
	destroy_token_list(token_list);
}

Ensure(parse_full_command, can_parse_3_pipe)
{
	//GIVEN (etant donné etat initial)
	t_token_list *token_list = init_token_list();
	t_token token1;
	t_token token2;
	t_token token3;
	t_token token4;
	t_token token5;
	t_token token6;
	t_token token7;
	t_token token8;
	t_token token9;
	t_token token10;
	t_token token11;
	t_node *head = NULL;

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
	token6.type = PIPE;
	token6.value = ft_strdup("|");
	token7.type = WORD;
	token7.value = ft_strdup("tamere");
	token8.type = WORD;
	token8.value = ft_strdup("-d");
	token9.type = PIPE;
	token9.value = ft_strdup("|");
	token10.type = WORD;
	token10.value = ft_strdup("tonpere");
	token11.type = WORD;
	token11.value = ft_strdup("fdp");

	add_token(token_list, token1);
	add_token(token_list, token2);
	add_token(token_list, token3);
	add_token(token_list, token4);
	add_token(token_list, token5);
	add_token(token_list, token6);
	add_token(token_list, token7);
	add_token(token_list, token8);
	add_token(token_list, token9);
	add_token(token_list, token10);
	add_token(token_list, token11);

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
	assert_that(right->type, is_equal_to(COMMAND_PIPE));
	assert_that(right->left->type, is_equal_to(SIMPLE_COMMAND));
	assert_that(right->left->vector_strs.values[0], is_equal_to_string("wc"));
	assert_that(right->left->vector_strs.values[1], is_equal_to_string("-l"));
	assert_that(right->left->vector_strs.values[2], is_equal_to_string(NULL));
	assert_that(right->left->left, is_equal_to(NULL));
	assert_that(right->right->type, is_equal_to(COMMAND_PIPE));
	assert_that(right->right->right->type, is_equal_to(SIMPLE_COMMAND));
	assert_that(right->right->right->vector_strs.values[0], is_equal_to_string("tonpere"));
	assert_that(right->right->right->vector_strs.values[1], is_equal_to_string("fdp"));
	assert_that(right->right->right->vector_strs.values[2], is_equal_to_string(NULL));
	assert_that(right->right->right->left, is_equal_to(NULL));
	assert_that(right->right->right->right, is_equal_to(NULL));
	assert_that(right->right->left->type, is_equal_to(SIMPLE_COMMAND));
	assert_that(right->right->left->vector_strs.values[0], is_equal_to_string("tamere"));
	assert_that(right->right->left->vector_strs.values[1], is_equal_to_string("-d"));
	assert_that(right->right->left->vector_strs.values[2], is_equal_to_string(NULL));
	assert_that(right->right->left->left, is_equal_to(NULL));

	clear_tree(head);
	destroy_token_list(token_list);
}

Ensure(parse_full_command, can_parse_2_pipe_with_redirections)
{
	//GIVEN (etant donné etat initial)
	t_token_list *token_list = init_token_list();
	t_token token1;
	t_token token2;
	t_token token3;
	t_token token4;
	t_token token5;
	t_token token6;
	t_token token7;
	t_token token8;
	t_token token9;
	t_token token10;
	t_token token11;
	t_node *head = NULL;

	token1.type = I_REDIRECTION;
	token1.value = ft_strdup("<");
	token2.type = WORD;
	token2.value = ft_strdup("infile");
	token3.type = WORD;
	token3.value = ft_strdup("wc");
	token4.type = WORD;
	token4.value = ft_strdup("-l");
	token5.type = PIPE;
	token5.value = ft_strdup("|");
	token6.type = I_REDIRECTION;
	token6.value = ft_strdup("<");
	token7.type = WORD;
	token7.value = ft_strdup("infile2");
	token8.type = WORD;
	token8.value = ft_strdup("wc");
	token9.type = WORD;
	token9.value = ft_strdup("-l");
	token10.type = PIPE;
	token10.value = ft_strdup("|");
	token11.type = WORD;
	token11.value = ft_strdup("fdp");

	add_token(token_list, token1);
	add_token(token_list, token2);
	add_token(token_list, token3);
	add_token(token_list, token4);
	add_token(token_list, token5);
	add_token(token_list, token6);
	add_token(token_list, token7);
	add_token(token_list, token8);
	add_token(token_list, token9);
	add_token(token_list, token10);
	add_token(token_list, token11);

	//WHEN (quand)
	head = parser(token_list);

	//THEN (alors)
	t_node *left = head->left;
	t_node *right = head->right;

	assert_that(head->type, is_equal_to(COMMAND_PIPE));
	assert_that(left->type, is_equal_to(COMMAND_I_REDIRECT));
	assert_that(left->left->type, is_equal_to(SIMPLE_COMMAND));
	assert_that(left->right->type, is_equal_to(COMMAND_I_REDIRECT));
	assert_that(left->right->vector_strs.values[0], is_equal_to_string("infile"));
	assert_that(left->right->right, is_equal_to(NULL));
	assert_that(left->right->left, is_equal_to(NULL));
	assert_that(left->left->vector_strs.values[0], is_equal_to_string("wc"));
	assert_that(left->left->vector_strs.values[1], is_equal_to_string("-l"));
	assert_that(left->left->vector_strs.values[2], is_equal_to_string(NULL));
	assert_that(left->left->left, is_equal_to(NULL));
	assert_that(left->left->right, is_equal_to(NULL));
	assert_that(right->type, is_equal_to(COMMAND_PIPE));
	assert_that(right->left->type, is_equal_to(COMMAND_I_REDIRECT));
	assert_that(right->left->right->vector_strs.values[0], is_equal_to_string("infile2"));
	assert_that(right->left->left->type, is_equal_to(SIMPLE_COMMAND));
	assert_that(right->left->left->vector_strs.values[0], is_equal_to_string("wc"));
	assert_that(right->left->left->vector_strs.values[1], is_equal_to_string("-l"));
	assert_that(right->left->left->vector_strs.values[2], is_equal_to_string(NULL));
	assert_that(right->left->left->left, is_equal_to(NULL));
	assert_that(right->left->left->right, is_equal_to(NULL));
	assert_that(right->right->type, is_equal_to(SIMPLE_COMMAND));
	assert_that(right->right->vector_strs.values[0], is_equal_to_string("fdp"));
	assert_that(right->right->vector_strs.values[1], is_equal_to_string(NULL));
	assert_that(right->right->left, is_equal_to(NULL));
	assert_that(right->right->right, is_equal_to(NULL));

	clear_tree(head);
	destroy_token_list(token_list);
}
