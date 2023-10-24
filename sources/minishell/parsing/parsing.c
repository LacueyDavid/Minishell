#include "parsing.h"
#include "lexer.h"
#include <stdlib.h>
#include "libft.h"
#include <stdbool.h>

t_node	*init_node(void)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = 0;
	node->values = NULL;
	node->values_capacity = 0;
	node->values_size= 0;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	clear_tree(t_node *node)
{
	if (!node)
		return ;
	clear_tree(node->left);
	clear_tree(node->right);
	free_strs(node->values);
	free(node);
}

bool	add_word(t_node *node, char *word)
{
	size_t	old_size;
	size_t	new_size;

	node->values_size++;
	if (node->values_capacity == 0)
	{
		node->values_capacity = 1;
		node->values = malloc(sizeof(char *) * (node->values_capacity + 1));
		if (!node->values)
			return (false);
	}
	if (node->values_capacity < node->values_size)
	{
		old_size = (node->values_capacity + 1) * sizeof(char *);
		node->values_capacity *= 2;
		new_size = (node->values_capacity + 1) * sizeof(char *);
		node->values = ft_realloc(node->values, new_size, old_size);
		if (!node->values)
			return (false);
	}
	node->values[node->values_size - 1] = ft_strdup(word);
	if (!node->values[node->values_size - 1])
		return (false);
	node->values[node->values_size] = NULL;
	return (true);
}

bool	create_simple_command_tree(t_node *node, t_token_list *token_list)
{
	size_t index;

	index = 0;
	while (index < token_list->size)
	{
		if (token_list->tokens[index].type == WORD)
			if (!add_word(node, token_list->tokens[index].value))
				return (false);
		if (!node)
			return (false);
		index++;
	}
	node->type = SIMPLE_COMMAND;
	return (true);
}

bool	create_o_redirection_tree(t_node *node, t_token_list *token_list)
{
	t_node	*left;
	t_node	*right;
	size_t	index;

	index = 0;
	left = init_node();
	right = init_node();
	if (!left || !right)
		return (false);
	while (token_list->size > index)
	{
		if (token_list->tokens[index].type == WORD)
		{
			if (!add_word(left, token_list->tokens[index].value))
				return (false);
		}
		else if (token_list->tokens[index].type == O_REDIRECTION)
		{
			index++;
			if (!add_word(right, token_list->tokens[index].value))
				return (false);
		}
		index++;
	}
	node->type = O_REDIRECTION;
	left->type = SIMPLE_COMMAND;
	right->type = SIMPLE_COMMAND;
	node->left = left;
	node->right = right;
	return (true);
}

bool	create_tree(t_node *node, t_token_list *token_list)
{
	size_t	index;

	index = 0;
	while (index < token_list->size)
	{
		while (index < token_list->size && token_list->tokens[index].type == WORD)
			index++;
		if (index < token_list->size && token_list->tokens[index].type == O_REDIRECTION)
		{
			return (create_o_redirection_tree(node, token_list));
		}
	}
	return (create_simple_command_tree(node, token_list));
}

t_node	*parsing(t_token_list *token_list)
{
	t_node	*node;

	node = init_node();
	if (!node)
		return (NULL);
	if (!create_tree(node, token_list))
	{
		clear_tree(node);
		return (NULL);
	}
	return (node);
}
