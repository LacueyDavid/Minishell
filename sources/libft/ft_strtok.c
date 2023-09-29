#include "libft.h"

char	*extract_token(char *str_to_tokenize, size_t token_size)
{
	char 	*token;
	size_t 	index;
	
	index = 0;
	token = malloc(sizeof(char) * (token_size + 1));
	if (!token)
		return (NULL);
	while (index < token_size)
	{
		token[index] = str_to_tokenize[index];
		index++;
	}
	token[index] = '\0';
	return (token);
}

static char	**init_tokens(char *str_to_tokenize, char *separators)
{
	char	**tokens;
	size_t	tokens_counted;

	if (!str_to_tokenize || !separators)
		return (NULL);
	tokens_counted = count_tokens(str_to_tokenize, separators);
	tokens = malloc(sizeof(char *) * (tokens_counted + 1));
	if (!tokens)
		return (NULL);
	tokens[tokens_counted] = NULL;
	return (tokens);
}

char	**ft_strtok(char *str_to_tokenize, char *separators)
{
	char 	**tokens;
	size_t	token_size;
	size_t	tokens_index;

	tokens_index = 0;
	tokens = init_tokens(str_to_tokenize, separators);
	if (!tokens)
		return (NULL);
	while (*str_to_tokenize != '\0')
	{
		if (is_separators(*str_to_tokenize, separators))
			str_to_tokenize++;
		else
		{
			token_size = current_token_len(str_to_tokenize, separators);
			tokens[tokens_index] = extract_token(str_to_tokenize, token_size);
			if(extract_token_malloc_fail(tokens, tokens_index))
				return (NULL);
			str_to_tokenize += token_size;
			tokens_index++;
		}
	}
	return (tokens);
}
