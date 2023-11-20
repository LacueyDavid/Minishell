
#include <stdio.h>
#include <stdbool.h>
#include "parser.h"

bool is_node_visited(t_node *node, t_node **visited, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        if (visited[i] == node) {
            return true;
        }
    }
    return false;
}

void print_node_recursive(t_node *node, int depth, t_node **visited, size_t *visited_count, int max_depth) {
    if (node == NULL || is_node_visited(node, visited, *visited_count) || depth >= max_depth) {
        return;
    }
    visited[*visited_count] = node;
    (*visited_count)++;
    for (int i = 0; i < depth; ++i) {
        printf("  ");
    }
    printf("Node Type: %d\n", node->type);
    if (node->left == NULL && node->right == NULL)
        return ;
    print_node_recursive(node->head, depth + 1, visited, visited_count, max_depth);
    //print_node_recursive(node->parent, depth + 1, visited, visited_count, max_depth);
    print_node_recursive(node->left, depth + 1, visited, visited_count, max_depth);
    print_node_recursive(node->right, depth + 1, visited, visited_count, max_depth);
}

void print_node(t_node *node, int max_depth) {
    size_t visited_count = 0;
    t_node *visited[100];

    print_node_recursive(node, 0, visited, &visited_count, max_depth);
}

void print_parser_env(t_parser_env *env) 
{
    if (env == NULL) 
    {
        printf("Parser environment is NULL.\n");
        return;
    }
    printf("Number of Pipes: %zu\n", env->number_of_pipes);
    printf("Head Node:\n");
    print_node(env->head, 5);
    printf("Temporary Node: %p\n", (void *)env->temporary);
    printf("Simple Command Node: %p\n", (void *)env->simple_command);
    printf("Parser Map:\n");
    for (int i = 0; i < NUMBER_OF_TOKEN_TYPES; ++i)
        printf("  Token Type %d: %p\n", i, (void *)env->parser_map[i].function);
}