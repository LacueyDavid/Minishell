# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/10 21:05:04 by dlacuey           #+#    #+#              #
#    Updated: 2023/10/21 02:03:50 by dlacuey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3 -fPIC

LDFLAGS = $(LIBFT) -lreadline

CPPFLAGS = 	-I sources/libft/					\
			-I sources/get_next_line/			\
			-I sources/minishell/				\
			-I sources/minishell/lexing/		\
			-I sources/minishell/execution/		\
			-I sources/minishell/parsing/		\

OBJS =												\
													\
				$(addprefix sources/,				\
				main.o								\
				$(addprefix minishell/,				\
				minishell.o							\
				$(addprefix execution/,				\
				execution.o							\
												)	\
				$(addprefix parsing/,				\
				parsing.o						)	\
													\
				$(addprefix lexing/,				\
				lexer.o								\
				token_list.o						\
												))	\
													\
				$(addprefix get_next_line/,			\
				get_next_line.o						\
				get_next_line_utils.o			))	\
													\

TEST_OBJS =												\
														\
				sources/minishell/lexing/test_lexer.o	\
				sources/minishell/execution/test_exec.o	\
				sources/minishell/parsing/test_parsing.o\
														\

NAME = minishell
LIBFT = sources/libft/libft.a
LIBFTPATH = sources/libft/

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFTPATH)

libft: $(LIBFT)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFTPATH)
	$(CC) -o $(NAME) $^ $(LDFLAGS)

clean:
	$(RM) $(OBJS) $(OBJS_BONUS) $(TEST_OBJS)
	$(MAKE) clean -C $(LIBFTPATH)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFTPATH)
	$(RM) libtest.so

re: fclean all

check_func: all
	pharaoh tests_e2e/

check_unit: libtest.so
	cgreen-runner $^

check: check_unit check_func

libtest.so: $(TEST_OBJS) $(OBJS) $(LIBFT)
	$(CC) -shared -o $@ $^ $(LDFLAGS)

.PHONY: all clean fclean re libft check check_func check_unit
