/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:39:23 by jdenis            #+#    #+#             */
/*   Updated: 2023/12/20 14:39:23 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"
#include "colors.h"
#include "libft.h"

char	*ft_strchr_with_quote(const char *s, int c)
{
    bool    single_quote;
    bool    double_quote;

    single_quote = false;
    double_quote = false;
	while (*s)
	{
        if (*s == '\'')
            single_quote = !single_quote;
        if (*s == '\"')
            double_quote = !double_quote;
        if (*s == (char)c && !single_quote && !double_quote)
            return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

int hasWildcard(const char *str) 
{
    return ft_strchr_with_quote(str, '*') != NULL;
}

int match_end(char *file) 
{
    size_t  index;

    index = 0;
    while (file[index] == '*')
        index++;
    if (file[index] == '\0' || file[index] == '*')
        return (1);
    return (0);
}

int	wildcard_match(const char *dir_file, char *wildcarded_file) 
{
    while (*dir_file && *wildcarded_file) 
	{
        if (*wildcarded_file == '*') 
		{
            while (*wildcarded_file == '*') 
                wildcarded_file++;
            if (*wildcarded_file == '\0') 
                return 1;
            while (*dir_file) 
			{
                if (wildcard_match(dir_file, wildcarded_file)) 
                    return 1;
                dir_file++;
            }
            return 0;
        }
        if (*dir_file != *wildcarded_file) 
            return 0;
        dir_file++;
        wildcarded_file++;
    }
	if (*dir_file == '\0' && match_end(wildcarded_file))
    	return (1);
	return 0;
}

void add_file(char ***values, char *file) 
{
    size_t	index;
	size_t	index2;
	char	**new_values;

	index = 0;
	index2 = 0;
    while ((*values)[index]) 
        index++;
    new_values = (char **)malloc(sizeof(char *) * (index + 2));
    while (index2 < index)
	{
        new_values[index2] = ft_strdup((*values)[index2]);
		index2++;
	}
    new_values[index] = ft_strdup(file);
    new_values[index + 1] = NULL;
    free_strs(*values);
    *values = new_values;
}

size_t  count_files(char **values, char *file) 
{
    size_t  index;
    size_t  index2;

    index = 0;
    index2 = 0;
    while (values[index]) 
    {
        if (strcmp(values[index], file) != 0) 
            index2++;
        index++;
    }
    return (index2);
}

void remove_file(char ***values, char *file) 
{
    size_t	index;
	size_t	index2;
	char	**new_values;

    new_values = (char **)malloc(sizeof(char *) * (count_files(*values, file) + 1));
    index = 0;
    index2 = 0;
    while ((*values)[index]) 
	{
        if (strcmp((*values)[index], file) != 0) 
		{
            new_values[index2] = ft_strdup((*values)[index]);
            index2++;
		}
		index++;
    }
    new_values[index2] = NULL;
    free_strs(*values);
    *values = new_values;
}

void add_new_files(char *entry, char ***new_files) 
{
    char *new_file;
    size_t num_files;

    new_file = ft_strdup(entry);
    if (*new_files == NULL) 
    {
        *new_files = (char **)malloc(sizeof(char *) * 2);
        if (*new_files == NULL)
            exit(1);
        (*new_files)[0] = new_file;
        (*new_files)[1] = NULL;
    }
    else 
    {
        num_files = 0;
        while ((*new_files)[num_files] != NULL) 
            num_files++;
        *new_files = (char **)realloc(*new_files, sizeof(char *) * (num_files + 2));
        if (!new_files)
            (free_strs(*new_files), exit(1));
        (*new_files)[num_files] = new_file;
        (*new_files)[num_files + 1] = NULL;
    }
}

void    change_files(char ***values, char *wildcarded_file, char **new_files) 
{
    size_t  num_files;

    if (new_files != NULL) 
	{
		remove_file(values, wildcarded_file);
        num_files = 0;
        while (new_files[num_files] != NULL) 
		{
            add_file(values, new_files[num_files]);
            num_files++;
        }
        free_strs(new_files);
    }
}

void check_wildcards(char ***values, char *wildcarded_file) 
{
    DIR 			*dir;
    struct dirent	*entry;
    char            *name;
    char			**new_files;

	new_files = NULL;
	dir = opendir(".");
	if (dir == NULL) 
	{
        perror(RED"opendir");
        exit(1);
    }
    while ((entry = readdir(dir)) != NULL) 
	{
        if (ft_strchr(wildcarded_file, '/') == NULL)
            name = ft_strdup(entry->d_name);
        else
        {
            if (entry->d_type == DT_DIR)
                name = ft_strjoin(entry->d_name, "/");
            else
                name = ft_strdup(entry->d_name);
        }
        if (wildcard_match(name, wildcarded_file) && name[0] != '.')
            add_new_files(name, &new_files);
        free(name);
    }
    closedir(dir);
    change_files(values, wildcarded_file, new_files);
}

void wildcards(char ***values) 
{
    size_t	index;
	
	index  = 0;
    while ((*values)[index]) 
	{
        if (hasWildcard((*values)[index])) 
            check_wildcards(values, (*values)[index]);
        index++;
    }
}