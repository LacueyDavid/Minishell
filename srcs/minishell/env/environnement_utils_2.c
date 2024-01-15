/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement_utils_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:44:16 by jdenis            #+#    #+#             */
/*   Updated: 2024/01/15 21:51:32 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environnement.h"
#include "builtins.h"

int	size_of_new_env(int fd)
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

	length = 100;
	index = 0;
	new = malloc(sizeof(char *) * (length + 1));
	if (!new)
		return (NULL);
	str = get_next_line(fd);
	while (str)
	{
		new[index] = ft_strdup(str);
		free(str);
		new[index][ft_strlen(new[index]) - 1] = '\0';
		if (!new[index])
		{
			free_strs(new);
			return (NULL);
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

	length = 100;
	index = 0;
	new = malloc(sizeof(char *) * (length + 1));
	if (!new)
		return (NULL);
	str = get_next_line(fd);
	while (str)
	{
		new[index] = ft_strdup(str);
		free(str);
		new[index][ft_strlen(new[index]) - 1] = '\0';
		if (!new[index])
		{
			free_strs(new);
			return (NULL);
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
	int		fd;
	char	*path;

	path = getenv("HOME");
	if (!path)
	{
		perror(RED "Cannot find home path" WHITE);
		return ;
	}
	path = ft_strjoin(path, "/.temporary_export_minishell");
	if (access(path, F_OK) != -1)
	{
		fd = open(path, O_RDONLY, 0644);
		if (fd < 0)
		{
			perror(RED "Cannot open temporary export file" WHITE);
			return ;
		}
		free_strs(envs->exports);
		envs->exports = copy_export_from_file(fd);
		close(fd);
		unlink(path);
	}
	free(path);
}

void	update_env(t_envs *envs)
{
	int		fd;
	char	*path;
	char	*pwd;

	path = getenv("HOME");
	if (!path)
	{
		perror(RED "Cannot find home path" WHITE);
		return ;
	}
	path = ft_strjoin(path, "/.temporary_env_minishell");
	if (access(path, F_OK) != -1)
	{
		fd = open(path, O_RDONLY, 0644);
		if (fd < 0)
		{
			perror(RED "Cannot open temporary env file" WHITE);
			free(path);
			return ;
		}
		free_strs(envs->env);
		envs->env = copy_environnement_from_file(fd);
		close(fd);
		unlink(path);
		pwd = ft_getenv("PWD", envs);
		if (chdir(pwd) != 0)
			perror(RED "Cannot change directory" WHITE);
		free(pwd);
	}
	free(path);
}
