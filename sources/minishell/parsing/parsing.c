#include "parsing.h"
#include "lexer.h"
#include <stdlib.h>
#include "libft.h"

t_node	*init_node(void)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = 0;
	node->value = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_node	*parsing(t_token_list *token_list)
{
	t_node	*node;
	size_t	index;

	index = 0;
	node = init_node();
	if (!node )
		return (NULL);
	node->value = malloc(sizeof(char *) * (token_list->size + 1));
	if (!node->value)
		return (NULL);
	while (index < token_list->size)
	{
		node->value[index] = ft_strdup(token_list->tokens[index].value);
		index++;
	}
	node->value[index] = NULL;
	node->type = SIMPLE_COMMAND;
	return (node);
}
