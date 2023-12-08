/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 08:05:12 by jdenis            #+#    #+#             */
/*   Updated: 2023/12/04 11:25:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <cgreen/cgreen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Describe(ft_pwd);
BeforeEach(ft_pwd){}
AfterEach(ft_pwd){}

Ensure(ft_pwd, classic)
{
	int			output;

	output = ft_pwd();

	assert_that(output, is_equal_to(EXIT_SUCCESS));
}
