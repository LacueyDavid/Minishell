/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:37:17 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/07 16:36:01 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

char	**ft_strtok(char *str, char *charset);
char	**find_paths(char **envp);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_itoa(int n);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_isprint(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isalpha(int character);
int		ft_isdigit(int character);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_atoi(const char *nptr);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strslen(char **strs);
void	delete_newline(char **input);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_putnbr_fd(int n, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_bzero(void *s, size_t n);
void	free_strs(char **strs);
void	ft_strs_to_ints(int *array, char **argv);
void	ft_bubble_sort(int *array, size_t size);
void	ft_swap(int *a, int *b);
void	print_str(char *str);
void	*ft_realloc(void *ptr, size_t new_size, size_t old_size);
char	*ft_strsjoin(char **strs, char *sep);
bool	ft_strbstr(char *str, char *bstr, size_t len_bstr);
long	ft_atol(const char *nptr);
char	*ft_ltoa(long n);
// STRTOK
typedef struct s_count
{
	size_t	count;
	size_t	tokens;
	size_t	index;
	bool	single_quote;
	bool	double_quote;
}	t_count;

typedef struct s_extract_token
{
	char	**tokens;
	bool	single_quote;
	bool	double_quote;
	size_t	index;
	size_t	token_len;
}	t_extract_token;

char	**ft_strtok(char *str_to_tokenise, char *separators);
size_t	current_token_len(char *str_to_tokenize, char *separators);
ssize_t	count_tokens(char *str_to_tokenize, char *separators);
void	free_all(char **tokens);
bool	is_separators(char current_char, char *separators);
bool	extract_token_malloc_fail(char **tokens, size_t tokens_index);
bool	ft_add_char(char **str, char c);
void	init_count(t_count *count);
void	update_quotes_to_count_tokens(bool *single_quote, bool *double_quote,
			char current_char);
bool	init_extract_tokens(t_extract_token *extract_token,
			char *str_to_tokenize, char *separators);
void	update_quotes_to_extract_tokens(t_extract_token *extract_tokens,
			char *str_to_tokenize);
void	count_token_quoted_len(char *str_to_tokenize,
			t_extract_token *extract_tokens);
void	count_token_double_quoted_len(char *str_to_tokenize,
			t_extract_token *extract_tokens);
void	count_token_len(char *str_to_tokenize,
			t_extract_token *extract_tokens, char *separators);
char	*extract_token(char *str_to_tokenize, size_t token_size);

//
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_lstsize(t_list *lst);
void	ft_lstadd_front(t_list **lst, t_list *newlist);
void	ft_lstadd_back(t_list **lst, t_list *newlist);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);

#endif
