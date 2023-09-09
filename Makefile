# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/10 21:05:04 by dlacuey           #+#    #+#              #
#    Updated: 2023/09/09 23:26:19 by dlacuey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror

CPPFLAGS = 	-I sources/libft/					\
			-I sources/get_next_line/			\
			-I sources/minishell/				\
			-I sources/minishell/execution/		\

OBJS =												\
													\
				$(addprefix sources/,				\
				main.o								\
				$(addprefix minishell/,				\
				minishell.o							\
				$(addprefix execution/,				\
				execution.o							\
												)	\
												)	\
				$(addprefix get_next_line/,			\
				get_next_line.o						\
				get_next_line_utils.o)			)	\
													\

NAME = minishell
LIBFT = sources/libft/libft.a
LIBFTPATH = sources/libft/

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFTPATH)
	$(CC) -o $(NAME) $^ -lreadline $(LIBFT)

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)
	$(MAKE) clean -C $(LIBFTPATH)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFTPATH)

re: fclean all

check: all
	pharaoh tests/tests_e2e/

.PHONY: all clean fclean re check
