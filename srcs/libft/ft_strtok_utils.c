#include "libft.h"
#include "../../includes/colors.h"

bool	is_separators(char current_char, char *separators)
{
	size_t	index;

	index = 0;
	if (!separators)
		return (false);
	while (separators[index] != '\0')
	{
		if (current_char == separators[index])
			return (true);
		index++;
	}
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

#include <stdio.h>
size_t	count_tokens(char *str_to_tokenize, char *separators)
{
	size_t	index;
	size_t	tokens;
	bool	single_quote;
	bool	double_quote;
	size_t count;

	single_quote = false;
	double_quote = false;
	count = 0;
	index = 0;
	tokens = 0;
	while (str_to_tokenize[index])
	{
		while (str_to_tokenize[index] && is_separators(str_to_tokenize[index], separators))
			index++;
		if (str_to_tokenize[index] == '\'' && !double_quote)
			single_quote = !single_quote;
		if (str_to_tokenize[index] == '\"' && !single_quote)
			double_quote = !double_quote;
		if (single_quote)
		{
			index++;
			while (str_to_tokenize[index] && str_to_tokenize[index] != '\'')
				index++;
			if (str_to_tokenize[index] == '\'')
				single_quote = !single_quote;
			index++;
			tokens++;
		}
		else if (double_quote)
		{
			index++;
			while (str_to_tokenize[index] && str_to_tokenize[index] != '\"')
			{
				index++;
			}
			if (str_to_tokenize[index] == '\"')
			{
				double_quote = !double_quote;
			}
			index++;
			tokens++;
		}
		if (str_to_tokenize[index] && !is_separators(str_to_tokenize[index], separators)
			&& str_to_tokenize[index] != '\'' && str_to_tokenize[index] != '\"')
		{
			tokens++;
			while (str_to_tokenize[index] && !is_separators(str_to_tokenize[index], separators)
				   && str_to_tokenize[index] != '\'' && str_to_tokenize[index] != '\"')
				index++;
		}
		if (str_to_tokenize[index] == '\"' || str_to_tokenize[index] == '\'')
			continue ;
		if (tokens > 0)
			count++;
		tokens = 0;
	}
	if (single_quote || double_quote)
	{
		perror(RED"Error: unclosed quote\n"WHITE);
		return (0);
	}
	return (count);
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

