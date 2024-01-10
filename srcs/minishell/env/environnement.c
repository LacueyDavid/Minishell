/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:06:05 by jdenis            #+#    #+#             */
/*   Updated: 2024/01/10 16:31:07 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environnement.h"
#include <stdlib.h>
#include "libft.h"
#include <stdio.h>
#include <fcntl.h>
#include "colors.h"
#include "get_next_line.h"
#include "builtins.h"

extern char **environ;

void	sort(char **exports)
{
	size_t	index;
	size_t	index2;
	char	*tmp;

	index = 0;
	index2 = 0;
	while (exports[index])
	{
		index2 = index + 1;
		while (exports[index2])
		{
			if (ft_strcmp(exports[index], exports[index2]) > 0)
			{
				tmp = exports[index];
				exports[index] = exports[index2];
				exports[index2] = tmp;
			}
			index2++;
		}
		index++;
	}
}

char	*ft_strdup_with_quotes(char *str)
{
	char	*new;
	size_t	index;
	size_t	index2;
	size_t	index3;
	bool	equal;

	index = 0;
	index2 = 0;
	index3 = 0;
	equal = false;
	new = malloc(ft_strlen(str) + 3);
	if (!new)
		return NULL;
	while (str[index])
	{
		new[index2] = str[index];
		if (str[index] == '=' && !equal)
		{
			equal = true;
			index2++;
			new[index2] = '"';
			index3 = index2;
		}
		index++;
		index2++;
	}
	if (new[index3] == '"')
	{
		new[index2] = '"';
		index2++;
	}
	new[index2] = '\0';
	return (new);
}

void	redo_export(t_envs *envs)
{
	size_t	index;
	int 	fd;
	char 	*path;

	index = 0;
	path = getenv("HOME");
	if (!path)
	{
		perror(RED"Cannot find home path"WHITE);
		return ;
	}
	path = ft_strjoin(path, "/.temporary_export_minishell");
	fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0) 
	{
		perror(RED"Cannot open temporary export file"WHITE);
		return ;
	}
	while (envs->exports[index])
	{
		write(fd, envs->exports[index], ft_strlen(envs->exports[index]));
		write(fd, "\n", 1);
		index++;
	}
	free(path);
	close(fd);
}

void	redo_env(t_envs *envs)
{
	size_t	index;
	int 	fd;
	char 	*path;

	index = 0;
	path = getenv("HOME");
	if (!path)
	{
		perror(RED"Cannot find home path"WHITE);
		return ;
	}
	path = ft_strjoin(path, "/.temporary_env_minishell");
	fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0) 
	{
		perror(RED"Cannot open temporary env file"WHITE);
		return ;
	}
	while (envs->env[index])
	{
		write(fd, envs->env[index], ft_strlen(envs->env[index]));
		write(fd, "\n", 1);
		index++;
	}
	free(path);
	close(fd);
}

void	redo_envs(t_envs *envs)
{
	redo_env(envs);
	redo_export(envs);
}

int 	size_of_new_env(int fd)
{
	char	*str;
	int		size;
	int		fd_copy;

	size = 0;
	fd_copy = fd;
	str = get_next_line(fd_copy);
	while (str)
	{
		size++;
		free(str);
		str = get_next_line(fd_copy);
	}
	free(str);
	return (size);
}

char	**copy_environnement_from_file(int fd)
{
	size_t	index;
	size_t	length;
	char	**new;
	char	*str;

	// length = size_of_new_env(fd);
	length = 100;
	index = 0;
	new = malloc(sizeof(char *) * (length + 1));
	if (!new)
		return NULL;
	str = get_next_line(fd);
	while (str)
	{
		new[index] = ft_strdup(str);
		free(str);
		new[index][ft_strlen(new[index]) - 1] = '\0';
		if (!new[index])
		{
			free_strs(new);
			return NULL;
		}
		str = get_next_line(fd);
		index++;
	}
	free(str);
	new[index] = NULL;
	return (new);
}

char	**copy_export_from_file(int fd)
{
	size_t	index;
	size_t	length;
	char	**new;
	char	*str;

	// length = size_of_new_env(fd);
	length = 100;
	index = 0;
	new = malloc(sizeof(char *) * (length + 1));
	if (!new)
		return NULL;
	str = get_next_line(fd);
	while (str)
	{
		new[index] = ft_strdup(str);
		free(str);
		new[index][ft_strlen(new[index]) - 1] = '\0';
		if (!new[index])
		{
			free_strs(new);
			return NULL;
		}
		str = get_next_line(fd);
		index++;
	}
	free(str);
	new[index] = NULL;
	sort(new);
	return (new);
}

void	update_export(t_envs *envs)
{
	int 	fd;
	char 	*path;

	path = getenv("HOME");
	if (!path)
	{
		perror(RED"Cannot find home path"WHITE);
		return ;
	}
	path = ft_strjoin(path, "/.temporary_export_minishell");
	if (access(path, F_OK) != -1)
	{
		fd = open(path, O_RDONLY, 0644);
		if (fd < 0) 
		{
			perror(RED"Cannot open temporary export file"WHITE);
			return ;
		}
		free_strs(envs->exports);
		envs->exports = copy_export_from_file(fd);
		close(fd);
		unlink(path);
		free(path);
	}
}

void	update_env(t_envs *envs)
{
	int 	fd;
	char 	*path;

	path = getenv("HOME");
	if (!path)
	{
		perror(RED"Cannot find home path"WHITE);
		return ;
	}
	path = ft_strjoin(path, "/.temporary_env_minishell");
	if (access(path, F_OK) != -1)
	{
		fd = open(path, O_RDONLY, 0644);
		if (fd < 0) 
		{
			perror(RED"Cannot open temporary env file"WHITE);
			return ;
		}
		free_strs(envs->env);
		envs->env = copy_environnement_from_file(fd);
		close(fd);
		unlink(path);
		free(path);
		path = ft_getenv("PWD", envs);
		if (chdir(path) != 0)
			perror(RED"Cannot change directory"WHITE);
		free(path);
	}
}

void	update_envs(t_envs *envs)
{
	update_env(envs);
	update_export(envs);
}

void	free_envs(t_envs *envs)
{
	free_strs(envs->env);
	free_strs(envs->exports);
	free(envs);
}

char	**copy_environnement()
{
	size_t	index;
	size_t	length;
	char	**new;

	length = 0;
	index = 0;
	while (environ[length])
		length++;
	new = malloc(sizeof(char *) * (length + 1));
	if (!new)
		return NULL;
	while (environ[index])
	{
		new[index] = ft_strdup(environ[index]);
		if (!new[index])
		{
			free_strs(new);
			return NULL;
		}
		index++;
	}
	new[index] = NULL;
	return (new);
}

char	*increased_shlvl(char *str)
{
	char	*new;
	int		shlvl;
	char	*tmp;

	shlvl = ft_atoi(str + 6);
	shlvl++;
	tmp = ft_itoa(shlvl);
	new = ft_strjoin("SHLVL=", tmp);
	free(tmp);
	return (new);
}

//pour pouvoir faire un export seul, difference : c'est dans l'ordre alphabetique, avec la valeur des variables entre doubel quotes et on ne prend pas les _=/usr/bin/env
char **copy_env_export()
{
	size_t	index;
	size_t	index2;
	size_t	length;
	char 	**new;

	length = 0;
	index = 0;
	index2 = 0;
	while (environ[length])
		length++;
	new = malloc(sizeof(char *) * (length));
	if (!new)
		return NULL;
	while (environ[index])
	{
		if (ft_strncmp(environ[index], "SHLVL=", 6) == 0)
		{
			new[index2] = ft_strdup_with_quotes(increased_shlvl(environ[index]));
			if (!new[index2])
			{
				free_strs(new);
				return NULL;
			}
			index2++;
		}
		if (!(environ[index][0] == '_' && environ[index][1] == '='))
		{
			new[index2] = ft_strdup_with_quotes(environ[index]);
			if (!new[index2])
			{
				free_strs(new);
				return NULL;
			}
			index2++;
		}
		index++;
	}
	new[index2] = NULL;
	sort(new);
	return (new);
}

t_envs	*copy_env_and_export(void)
{
	t_envs	*envs;

	envs = malloc(sizeof(t_envs));
	if (!envs)
		return (NULL);
	envs->env = copy_environnement();
	envs->exports = copy_env_export();
	if (!envs->exports || !envs->env)
	{
		free_envs(envs);
		return (NULL);
	}
	return (envs);
}