# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/16 04:53:25 by jdenis            #+#    #+#              #
#    Updated: 2023/09/20 11:48:35 by jdenis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -fPIC -Wall -Wextra -Werror -g3

all: cd echo env exit expo pwd unset

test: echo pwd

libtestcd.so: test_cd.o ft_cd.o
	@$(CC) $(CFLAGS) -shared -o $@ $^

libtestecho.so: test_echo.o ft_echo.o
	@$(CC) $(CFLAGS) -shared -o $@ $^

libtestenv.so: test_env.o ft_env.o
	@$(CC) $(CFLAGS) -shared -o $@ $^

libtestexit.so: test_exit.o ft_exit.o
	@$(CC) $(CFLAGS) -shared -o $@ $^

libtestexport.so: test_export.o ft_export.o
	@$(CC) $(CFLAGS) -shared -o $@ $^

libtestpwd.so: test_pwd.o ft_pwd.o
	@$(CC) $(CFLAGS) -shared -o $@ $^

libtestunset.so: test_unset.o ft_unset.o
	@$(CC) $(CFLAGS) -shared -o $@ $^

cd: libtestcd.so
	@cgreen-runner $^

echo: libtestecho.so
	@cgreen-runner $^

env: libtestenv.so
	@cgreen-runner $^

exit: libtestexit.so
	@cgreen-runner $^

expo: libtestexport.so
	@cgreen-runner $^

pwd: libtestpwd.so
	@cgreen-runner $^

unset: libtestunset.so
	@cgreen-runner $^

clean:
	rm -f *.so *.o *.txt a.out

.PHONY: all test clean