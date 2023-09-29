#include "libft.h"

bool	is_separators(char current_char, char *separators)
{
	size_t	index;

	index = 0;
	while (separators[index] != '\0')
	{
		if (current_char == separators[index])
			return (true);
		index++;
	}
	if (current_char == '\0')
		return (true);
	return (false);
}

size_t	current_token_len(char *str_to_tokenize, char *separators)
{
	size_t count;

	count = 0;
	while (str_to_tokenize[count] && is_separators(str_to_tokenize[count], separators) == 0)
		count++;
	return count;
}

void	free_all(char **tokens)
{
	size_t	index;

	index = 0;
	while (tokens[index])
	{
		free(tokens[index]);
		index++;
	}
	free(tokens);
}

size_t	count_tokens(char *str_to_tokenize, char *separators)
{
	size_t	index;
	size_t	tokens;

	index = 0;
	tokens = 0;
	while (str_to_tokenize[index] != '\0')
	{
		if (is_separators(str_to_tokenize[index + 1], separators))
			if (!is_separators(str_to_tokenize[index], separators))
				tokens++;
		index++;
	}
	return (tokens);
}

bool	extract_token_malloc_fail(char **tokens, size_t tokens_index)
{
	if (!tokens[tokens_index])
	{
		free_all(tokens);
		return (true);
	}
	return (false);
}

