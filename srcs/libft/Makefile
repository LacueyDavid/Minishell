CC = cc

CFLAGS = -Wall -Wextra -Werror

OBJS = 			ft_isdigit.o				\
				ft_isalpha.o				\
				ft_isalnum.o				\
				ft_isascii.o				\
				ft_isprint.o				\
				ft_strchr.o					\
				ft_strlcat.o				\
				ft_strrchr.o				\
				ft_tolower.o				\
				ft_toupper.o				\
				ft_strncmp.o				\
				ft_strnstr.o				\
				ft_memmove.o				\
				ft_strlen.o					\
				ft_bzero.o					\
				ft_memchr.o					\
				ft_memset.o					\
				ft_memcpy.o					\
				ft_strlcpy.o				\
				ft_strlcat.o				\
				ft_memcmp.o					\
				ft_atoi.o					\
				ft_calloc.o					\
				ft_substr.o					\
				ft_strjoin.o				\
				ft_strtrim.o				\
				ft_split.o					\
				ft_itoa.o					\
				ft_strmapi.o				\
				ft_striteri.o				\
				ft_putchar_fd.o				\
				ft_putstr_fd.o				\
				ft_putendl_fd.o				\
				ft_putnbr_fd.o				\
				ft_strdup.o					\
				ft_strs_to_ints.o			\
				ft_bubble_sort.o			\
				ft_swap.o					\
				ft_strslen.o				\
				ft_print_str.o				\
				ft_strcmp.o					\
				ft_find_paths.o				\
				ft_free_strs.o				\
				ft_delete_newline.o			\
				ft_realloc.o				\
				ft_strtok.o					\
				ft_strtok_utils.o			\
				ft_strtok_utils_2.o			\
				ft_strtok_utils_3.o			\
				ft_strtok_utils_4.o			\
				ft_strtok_utils_5.o			\
				ft_strsjoin.o				\
				ft_strbstr.o				\
				ft_add_char.o				\
				ft_atol.o					\
				ft_ltoa.o					\

OBJS_BONUS =	ft_lstnew.o					\
				ft_lstsize.o				\
				ft_lstlast.o				\
				ft_lstadd_back.o			\
				ft_lstdelone.o				\
				ft_lstclear.o				\
				ft_lstiter.o				\
				ft_lstmap.o					\
				ft_lstadd_front.o			\

NAME = libft.a

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) src $@ $^
	ranlib $@

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

bonus: $(OBJS_BONUS)
	$(AR) src $(NAME) $^
	ranlib $(NAME)

.PHONY: all clean fclean re bonus
