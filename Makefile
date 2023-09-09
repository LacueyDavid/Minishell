# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/10 21:05:04 by dlacuey           #+#    #+#              #
#    Updated: 2023/09/09 18:51:13 by dlacuey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror

CPPFLAGS = -Ilibft/ -Iget_next_line/

OBJS =												\
													\
				main.o								\
				$(addprefix get_next_line/,			\
				get_next_line.o						\
				get_next_line_utils.o)				\
													\

NAME = minishell
LIBFT = libft/libft.a

all: $(NAME)

$(LIBFT):
	make -C libft/

$(NAME): $(OBJS) $(LIBFT)
	$(CC) -o $(NAME) $^ -lreadline

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

check: all
	pharaoh tests/tests_e2e/

.PHONY: all clean fclean re bonus
