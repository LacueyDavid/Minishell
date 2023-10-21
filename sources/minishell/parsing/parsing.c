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

void	add_word(t_node *node, char *word)
{
	node->values_size++;
	if (node->values_capacity == 0)
	{
		node->values_capacity = 1;
		node->values = malloc(sizeof(char *) * (node->values_capacity + 1));
		if (!node->values)
		{
			clear_tree(node);
			return ;
		}
	}
	if (node->values_capacity < node->values_size)
	{
		node->values_capacity *= 2;
		node->values = ft_realloc(node->values, ((node->values_capacity + 1) * sizeof(char *)));
		if (!node->values)
		{
			clear_tree(node);
			return ;
		}
	}
	node->values[node->values_size - 1] = ft_strdup(word);
	if (!node->values[node->values_size - 1])
	{
		clear_tree(node);
		return ;
	}
	node->values[node->values_size] = NULL;
}

void	create_simple_command_tree(t_node *node, t_token_list *token_list)
{
	size_t index;

	index = 0;
	while (index < token_list->size)
	{
		if (token_list->tokens[index].type == WORD)
			add_word(node, token_list->tokens[index].value);
		if (!node)
			return ;
		index++;
	}
	node->type = SIMPLE_COMMAND;
}

void	create_o_redirection_tree(t_node *node, t_token_list *token_list)
{
	t_node	*left;
	t_node	*right;
	size_t	index;

	index = 0;
	left = init_node();
	right = init_node();
	if (!left || !right)
	{
		clear_tree(node);
		return ;
	}
	while (token_list->size > index)
	{
		if (token_list->tokens[index].type == WORD)
			add_word(left, token_list->tokens[index].value);
		else if (token_list->tokens[index].type == O_REDIRECTION)
		{
			index++;
			add_word(right, token_list->tokens[index].value);
		}
		if (!left || !right)
			return ;
		index++;
	}
	node->type = O_REDIRECTION;
	left->type = SIMPLE_COMMAND;
	right->type = SIMPLE_COMMAND;
	node->left = left;
	node->right = right;
}

void	create_tree(t_node *node, t_token_list *token_list)
{
	size_t	index;

	index = 0;
	while (index < token_list->size)
	{
		while (token_list->tokens[index].type == WORD)
			index++;
		if (token_list->tokens[index].type == O_REDIRECTION)
		{
			create_o_redirection_tree(node, token_list);
			return ;
		}
	}
	create_simple_command_tree(node, token_list);
}

t_node	*parsing(t_token_list *token_list)
{
	t_node	*node;

	node = init_node();
	if (!node )
		return (NULL);
	create_tree(node, token_list);
	return (node);
}
