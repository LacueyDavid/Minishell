#include "libft.h"
#include <stdio.h>

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
	if (tokens_counted == 0)
		return (NULL);
	tokens = malloc(sizeof(char *) * (tokens_counted + 1));
	if (!tokens)
		return (NULL);
	tokens[tokens_counted] = NULL;
	tokens[0] = NULL;
	return (tokens);
}

char	**ft_strtok(char *str_to_tokenize, char *separators)
{
	char 	**tokens;
	size_t	token_size;
	size_t	tokens_index;
	bool	single_quote;
	bool	double_quote;

	single_quote = false;
	double_quote = false;
	tokens_index = 0;
	token_size = 0;
	tokens = init_tokens(str_to_tokenize, separators);
	if (!tokens)
		return (NULL);
	if (tokens[0] && tokens[1] == NULL)
	{
		if(extract_token_malloc_fail(tokens, 0))
			return (NULL);
		return (tokens);
	}
	while (str_to_tokenize[token_size])
	{
		while (str_to_tokenize[token_size] && is_separators(str_to_tokenize[token_size], separators))
			str_to_tokenize++;
		if (str_to_tokenize[token_size] == '\'' && !double_quote)
			single_quote = !single_quote;
		if (str_to_tokenize[token_size] == '\"' && !single_quote)
			double_quote = !double_quote;
		if (single_quote)
		{
			token_size++;
			while (str_to_tokenize[token_size] && str_to_tokenize[token_size] != '\'')
				token_size++;
			if (str_to_tokenize[token_size] == '\'')
				single_quote = !single_quote;
			token_size++;
		}
		else if (double_quote)
		{
			token_size++;
			while (str_to_tokenize[token_size] && str_to_tokenize[token_size] != '\"')
				token_size++;
			if (str_to_tokenize[token_size] == '\"')
				double_quote = !double_quote;
			token_size++;
		}
		if (str_to_tokenize[token_size] && !is_separators(str_to_tokenize[token_size], separators)
				 && str_to_tokenize[token_size] != '\'' && str_to_tokenize[token_size] != '\"')
		{
			while (str_to_tokenize[token_size] && !is_separators(str_to_tokenize[token_size], separators)
				 && str_to_tokenize[token_size] != '\'' && str_to_tokenize[token_size] != '\"')
				token_size++;
		}
		if (str_to_tokenize[token_size] == '\'' || str_to_tokenize[token_size] == '\"')
			continue ;
		if (token_size > 0)
		{
			tokens[tokens_index] = extract_token(str_to_tokenize, token_size);
			if(extract_token_malloc_fail(tokens, tokens_index))
				return (NULL);
			str_to_tokenize += token_size;
			tokens_index++;
			token_size = 0;
		}
	}
	return (tokens);
}
