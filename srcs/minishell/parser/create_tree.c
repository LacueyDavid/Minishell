/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 05:20:23 by dlacuey           #+#    #+#             */
/*   Updated: 2023/11/22 23:39:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

static void	is_simple_command(t_node *node, t_node *simple_command)
{
	if (node == node->head)
	{
		node->vector_strs.values = simple_command->vector_strs.values;
		free(simple_command);
	}
	else
	{
		node->parent->left = simple_command;
		simple_command->parent = node->parent;
	}
}

static bool	create_nodes(t_parser_env *env, t_token *tokens, size_t *index)
{
	e_token_type	type;

	// printf("affichage de l'envirronement : \n");
	// print_parser_env(env);
	type = tokens[*index].type;
	if (type != WORD)
		(*index)++;
	if (!env->parser_map[type].function(env, tokens[*index]))
		return (false);
	return (true);
}

bool	create_redirection_tree(t_parser_env *env, t_token_list *token_list)
{
	size_t	index;

	index = 0;
	while (index < token_list->size)
	{
		if (!create_nodes(env, token_list->tokens, &index))
			return (false);
		index++;
	}
	is_simple_command(env->temporary, env->simple_command);
	return (true);
}

//TEST////////////////////////////////////////
//TEST////////////////////////////////////////
//TEST////////////////////////////////////////

t_token_list	*pipeless_token_list(t_token_list *token_list, size_t *index)
{
	t_token_list	*tmp;
	size_t			i;

	i = *index;
	tmp = init_token_list();
	// if (token_list->tokens[i].type == PIPE)
	// 	*index++;
	while (i < token_list->size && token_list->tokens[i].type != PIPE)
	{
		add_token(tmp, token_list->tokens[i]);
		i++;
	}
	*index = i;
	return (tmp);
}

bool	add_pipe(t_parser_env *env)
{
	t_node *node;

	env->number_of_pipes++;
	node = init_node();
	if (!node)
		return (false);
	node->type = COMMAND_PIPE;
	env->temporary->right = node;
	node->head = env->temporary->head;
	node->parent = env->temporary;
	env->temporary = node;
	return (true);
}

bool	is_pipes(t_token *tokens, size_t size)
{
	size_t	index;

	index = 0;
	while (index < size)
	{
		if (tokens[index].type == PIPE)
			return (true);
		index++;
	}
	return (false);
}

bool	copy_tree(t_node *node, t_node *tmp_node)
{
	if (node->left)
	{
		tmp_node->left = init_node();
		if (!tmp_node->left)
			return (false);
		tmp_node->left->parent = tmp_node;
		if (!copy_tree(node->left, tmp_node->left))
			return (false);
	}
	if (node->right)
	{
		tmp_node->right = init_node();
		if (!tmp_node->right)
			return (false);
		tmp_node->right->parent = tmp_node;
		if (!copy_tree(node->right, tmp_node->right))
			return (false);
	}
	tmp_node->type = node->type;
	tmp_node->vector_strs = node->vector_strs;
	return (true);
}

bool copy_env(const t_parser_env *env, t_parser_env *tmp_env_ptr) 
{
    if (!init_parser_env(tmp_env_ptr)) 
        return false;
    tmp_env_ptr->head = init_node();
    if (!tmp_env_ptr->head)
        return false;
    if (!copy_tree(env->head, tmp_env_ptr->head))
        return false;
    tmp_env_ptr->number_of_pipes = env->number_of_pipes;
    return true;
}

// bool	create_piped_tree(t_parser_env *env, t_token_list *token_list)
// {
// 	size_t			index;
// 	t_token_list	*tmp1;
// 	t_token_list	*tmp2;
// 	t_parser_env	tmp_env;

// 	index = 0;
// 	if(!copy_env(env, tmp_env))
// 		return (false);
// 	if (is_pipes(token_list->tokens, token_list->size))
// 	{
// 		printf("ok boi\n");
// 		env->head->type = COMMAND_PIPE;
// 		while (index < token_list->size)
// 		{
// 			printf("ok boi boi\n");
// 			if (index == 0)
// 				tmp1 = pipeless_token_list(token_list, &index);
// 			printf("pete les couilles\n");
// 			if (index < token_list->size)
// 				index++;
// 			tmp2 = pipeless_token_list(token_list, &index);
// 			printf("pete les couilles x2\n");
// 			if (!create_redirection_tree(&tmp_env, tmp1))
// 				return (false);
// 			printf("ok boi boi boi\n");
// 			if (index < token_list->size)
// 			{
// 				env->temporary->left = tmp_env.head;
// 				add_pipe(env);
// 			}
// 			else
// 			{
// 				env->temporary->left = tmp_env.head;
// 				clear_tree(tmp_env.head);
// 				if (!create_redirection_tree(&tmp_env, tmp2))
// 					return (false);
// 				env->temporary->right = tmp_env.head;
// 			}
// 			printf("ok boi boi boi boi\n");
// 			index++;
// 			destroy_token_list(tmp1);
// 			clear_tree(tmp_env.head);
// 			tmp1 = tmp2;
// 		}
// 		destroy_token_list(tmp1);
// 	}
// 	else
// 	{
// 		if (!create_redirection_tree(env, token_list))
// 			return (false);
// 	}
// 	return (true);
// }

void	clear_tree_head(t_node *node)
{
	if (!node)
		return ;
	clear_tree(node->left);
	clear_tree(node->right);
	free_strs(node->vector_strs.values);
}

bool	add_last_command(t_parser_env *env)
{
	t_node *node;

	node = init_node();
	if (!node)
		return (false);
	node->type = SIMPLE_COMMAND;
	env->temporary->right = node;
	node->head = env->temporary->head;
	node->parent = env->temporary;
	env->temporary = node;
	return (true);
}

t_vector_strs	copy_vector_strs(t_vector_strs vector_strs)
{
	t_vector_strs	tmp;
	size_t			index;

	index = 0;
	tmp.size = vector_strs.size;
	tmp.capacity = vector_strs.capacity;
	tmp.values = (char **)malloc(sizeof(char *) * (tmp.capacity + 1));
	if (!tmp.values)
		return ((t_vector_strs){0});
	while (index < tmp.size && vector_strs.values[index])
	{
		tmp.values[index] = ft_strdup(vector_strs.values[index]);
		if (!tmp.values[index])
		{
			free_strs(tmp.values);
			return ((t_vector_strs){0});
		}
		index++;
	}
	tmp.values[index] = NULL;
	return (tmp);
}

bool create_piped_tree(t_parser_env *env, t_token_list *token_list) 
{
    size_t index;
    t_token_list *tmp1;
    t_token_list *tmp2;
    t_parser_env *tmp_env;

    index = 0;
    tmp_env = (t_parser_env *)malloc(sizeof(t_parser_env));
    if (tmp_env == NULL)
        return false;

    tmp_env->head = (t_node *)malloc(sizeof(t_node));
    if (tmp_env->head == NULL) 
	{
        free(tmp_env);
        return false;
    }

    if (!copy_env(env, tmp_env))
        return false;

    if (is_pipes(token_list->tokens, token_list->size)) 
	{
        env->head->type = COMMAND_PIPE;

        while (index < token_list->size) 
		{
            if (index == 0)
                tmp1 = pipeless_token_list(token_list, &index);

            if (index < token_list->size)
                index++;

            tmp2 = pipeless_token_list(token_list, &index);

            if (!create_redirection_tree(tmp_env, tmp1))
                return false;

            if (index < token_list->size) 
			{
                env->head->left = tmp_env->head;
				env->head->left->vector_strs = copy_vector_strs(tmp_env->head->vector_strs);
                add_pipe(env);
            } 
			else 
			{
				// size_t index_test = 0;
				// printf("affichage des vector strs\n");
				// while(tmp_env->head->vector_strs.values[index_test])
				// {
				// 	printf("valeur du veceur %zu : %s\n", index_test, tmp_env->head->vector_strs.values[index_test]);
				// 	index_test++;
				// }
                add_last_command(env);
                env->head->left = tmp_env->head;
				env->head->left->vector_strs = copy_vector_strs(tmp_env->head->vector_strs);
                clear_tree_head(tmp_env->head);

                if (!create_redirection_tree(tmp_env, tmp2))
                    return false;

                env->head->right = tmp_env->head;
				env->head->right->vector_strs = copy_vector_strs(tmp_env->head->vector_strs);
            }

            destroy_token_list(tmp1);
            tmp1 = tmp2;
        }

        destroy_token_list(tmp1);
    } 
	else 
	{
        if (!create_redirection_tree(env, token_list))
            return false;
    }

    return true;
}

//TEST////////////////////////////////////////
//TEST////////////////////////////////////////
//TEST////////////////////////////////////////
