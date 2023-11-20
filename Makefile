# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/10 21:05:04 by dlacuey           #+#    #+#              #
#    Updated: 2023/11/20 18:42:14 by jdenis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3 -fPIC

LDFLAGS = $(LIBFT) -lreadline

CPPFLAGS = 	-I srcs/libft/								\
			-I srcs/get_next_line/						\
			-I srcs/minishell/							\
			-I srcs/minishell/lexer/					\
			-I srcs/minishell/execution/				\
			-I srcs/minishell/parser/					\
			-I srcs/minishell/history/					\
			-I srcs/minishell/wildcards/				\
			-I includes/								\

OBJS =													\
														\
				$(addprefix srcs/,						\
				main.o									\
														\
				$(addprefix get_next_line/,				\
				get_next_line.o							\
				get_next_line_utils.o			)		\
														\
				$(addprefix minishell/,					\
				minishell.o								\
														\
				$(addprefix history/,					\
				history.o						)		\
														\
				$(addprefix here_doc/,					\
				here_doc.o						)		\
														\
				$(addprefix wildcards/,					\
				wildcards.o						)		\
														\
				$(addprefix lexer/,						\
				lexer.o									\
				add_token.o								\
				destroy.o								\
				init_token_list.o						\
				lexer.o									\
				tokenize_splited_input.o		)		\
														\
				$(addprefix parser/,					\
				add_word.o								\
				clear_tree.o							\
				inits.o									\
				redirection_functions.o					\
				parser.o								\
				create_tree.o							\
				print_env.o								\
				update_vector_strs_capacity.o	)		\
														\
				$(addprefix execution/,					\
				execution.o								\
				init_exec.o								\
				redirections.o					)))		\
														\

TEST_OBJS =												\
														\
				srcs/minishell/lexer/test_lexer.o		\
				srcs/minishell/execution/test_exec.o	\
				srcs/minishell/parser/test_parser.o		\
				srcs/minishell/parser/test_pipeless_token_list.o		\
														\

NAME = minishell
LIBFT = srcs/libft/libft.a
LIBFTPATH = srcs/libft/

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
