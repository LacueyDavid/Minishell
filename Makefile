# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/10 21:05:04 by dlacuey           #+#    #+#              #
#    Updated: 2024/01/24 12:51:14 by dlacuey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3 -fPIC

LDFLAGS = $(LIBFT) -lreadline

CPPFLAGS = 	-I srcs/libft/													\
			-I srcs/get_next_line/											\
			-I srcs/minishell/												\
			-I srcs/minishell/lexer/										\
			-I srcs/minishell/execution/									\
			-I srcs/minishell/parser/										\
			-I srcs/minishell/history/										\
			-I srcs/minishell/wildcards/									\
			-I srcs/minishell/builtins/										\
			-I srcs/minishell/signals/										\
			-I srcs/minishell/here_doc/										\
			-I srcs/minishell/env/											\
			-I includes/													\

OBJS =																		\
																			\
				$(addprefix srcs/,											\
				main.o														\
																			\
				$(addprefix get_next_line/,									\
				get_next_line.o												\
				get_next_line_secure.o										\
				get_next_line_utils.o			)							\
																			\
				$(addprefix minishell/,										\
				minishell.o													\
																			\
				$(addprefix history/,										\
				history.o						)							\
																			\
				$(addprefix here_doc/,										\
				do_here_doc.o												\
				here_doc.o						)							\
																			\
				$(addprefix wildcards/,										\
				wildcards.o													\
				wildcards_utils.o											\
				wildcards_utils_2.o											\
				wildcards_utils.o				)							\
																			\
				$(addprefix signals/,										\
				signals.o						)							\
																			\
				$(addprefix lexer/,											\
				lexer.o														\
				ft_specialstrlen.o											\
				put_space_between_special_chars.o							\
				add_token.o													\
				destroy.o													\
				init_token_list.o											\
				tokenize_splited_input.o		)							\
																			\
				$(addprefix parser/,										\
				add_word.o													\
				clear_tree.o												\
				inits.o														\
				protections.o												\
				protections_2.o												\
				redirection_functions.o										\
				parser.o													\
				create_tree.o												\
				create_piped_tree.o											\
				create_tree_utils.o											\
				create_tree_utils_2.o										\
				parser_map.o												\
				update_vector_strs_capacity.o	)							\
																			\
				$(addprefix builtins/,										\
				ft_cd.o														\
				ft_cd_utils.o												\
				ft_echo.o													\
				ft_env.o													\
				ft_exit.o													\
				ft_export.o													\
				ft_pwd.o													\
				exec_builtin.o												\
				ft_export_utils.o											\
				ft_unset.o						)							\
																			\
				$(addprefix expand/,										\
				expand_env_variables.o										\
				count_final_value.o											\
				count_final_value_utils.o									\
				remove_quotes.o												\
				fill_final_value_utils.o									\
				fill_final_value.o				)							\
																			\
				$(addprefix env/,											\
				environnement_utils.o										\
				environnement_utils_2.o										\
				environnement_utils_3.o										\
				environnement_utils_4.o										\
				environnement_utils_5.o										\
				environnement.o					)							\
																			\
				$(addprefix execution/,										\
				do_builtin_or_execve.o										\
				exec_pipe.o													\
				protection.o												\
				wait_pids.o													\
				execution.o													\
				init_exec.o													\
				ft_get_command.o											\
				redirections.o					)))							\
																			\

TEST_OBJS =																	\
																			\
				srcs/minishell/lexer/test_lexer.o							\
				srcs/minishell/execution/test_exec.o						\
				srcs/minishell/parser/test_parser.o							\
				srcs/minishell/parser/test_pipeless_token_list.o			\
				srcs/minishell/builtins/test_echo.o							\
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
	$(CC) $(CFLAGS) -o $(NAME) $^ $(LDFLAGS)

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
