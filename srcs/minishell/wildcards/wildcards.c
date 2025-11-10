/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/12/20 14:39:23 by jdenis            #+#    #+#             */
/*   Updated: 2023/12/20 14:39:23 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"

void	remove_file(char ***values, char *file)
{
	size_t	index;
	size_t	index2;
	char	**new_values;

	new_values = (char **)malloc(sizeof(char *) * (count_files(*values, file)
				+ 1));
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

void	add_new_files(char *entry, char ***new_files)
{
	char	*new_file;
	size_t	num_files;

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
		*new_files = (char **)ft_realloc(*new_files, sizeof(char *) * (num_files
					+ 2), sizeof(char *) * (num_files + 1));
		if (!new_files)
			(free_strs(*new_files), exit(1));
		(*new_files)[num_files] = new_file;
		(*new_files)[num_files + 1] = NULL;
	}
}

void	change_files(char ***values, char *wildcarded_file, char **new_files)
{
	size_t	num_files;

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

void	check_wildcards(char ***values, char *wildcarded_file)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*name;
	char			**new_files;

	new_files = NULL;
	dir = opendir(".");
	if (dir == NULL)
	{
		perror(RED "opendir");
		exit(1);
	}
	entry = readdir(dir);
	while ((entry) != NULL)
	{
		name = name_file_or_dir(entry, wildcarded_file);
		if (wildcard_match(name, wildcarded_file) && name[0] != '.')
			add_new_files(name, &new_files);
		free(name);
		entry = readdir(dir);
	}
	closedir(dir);
	change_files(values, wildcarded_file, new_files);
}

void	wildcards(char ***values)
{
	size_t	index;

	index = 0;
	while ((*values)[index])
	{
		if (ft_strchr_with_quote((*values)[index], '*'))
			check_wildcards(values, (*values)[index]);
		index++;
	}
}
