/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pipeless_token_list.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:36:06 by jdenis            #+#    #+#             */
/*   Updated: 2024/01/15 18:32:44 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "fcntl.h"
#include "lexer.h"
#include "libft.h"
#include "parser.h"
#include "unistd.h"
#include <cgreen/cgreen.h>
#include <stdlib.h>
#include <string.h>

Describe(pipeless_token_list);

BeforeEach(pipeless_token_list)
{
}

AfterEach(pipeless_token_list)
{
}

Ensure(pipeless_token_list, can_parse_pipe)
{
	t_token_list	*token_list;
	t_token			token1;
	t_token			token2;
	t_token			token3;
	t_token			token4;
	t_token			token5;
	t_token_list	*token_list_test;
	t_token_list	*token_list_test2;
	size_t			index;

	//GIVEN (etant donné etat initial)
	token_list = init_token_list();
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
	index = 0;
	token_list_test = pipeless_token_list(token_list, &index);
	index++;
	token_list_test2 = pipeless_token_list(token_list, &index);
	//THEN (alors)
	assert_that(token_list_test->tokens[0].value, is_equal_to_string("echo"));
	assert_that(token_list_test->tokens[1].value, is_equal_to_string("toto"));
	// assert_that(token_list_test->tokens[2].value, is_equal_to_string(NULL));
	assert_that(token_list_test2->tokens[0].value, is_equal_to_string("wc"));
	assert_that(token_list_test2->tokens[1].value, is_equal_to_string("-l"));
	assert_that(token_list->size, is_equal_to(5));
	assert_that(token_list_test->size, is_equal_to(2));
	assert_that(token_list_test2->size, is_equal_to(2));
	destroy_token_list(token_list);
}
