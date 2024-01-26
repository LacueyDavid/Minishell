/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement_utils_4.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:44:25 by jdenis            #+#    #+#             */
/*   Updated: 2024/01/26 16:11:33 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environnement.h"

size_t	error_fd(char *path, char *str)
{
	free(path);
	perror(str);
	return (0);
}

char	*env_path(void)
{
	char	*path;

	path = getenv("HOME");
	if (!path)
	{
		perror(RED "Cannot find home path" WHITE);
		return (NULL);
	}
	path = ft_strjoin(path, "/.temporary_env_minishell");
	return (path);
}

char	*exp_path(void)
{
	char	*path;

	path = getenv("HOME");
	if (!path)
	{
		perror(RED "Cannot find home path" WHITE);
		return (NULL);
	}
	path = ft_strjoin(path, "/.temporary_export_minishell");
	return (path);
}

size_t	size_of_new_exp(void)
{
	int		fd;
	char	*path;
	size_t	length;
	char	*str;

	length = 1;
	path = exp_path();
	if (!path)
		return (0);
	if (access(path, F_OK) != -1)
	{
		fd = open(path, O_RDONLY, 0644);
		if (fd < 0)
			return (error_fd(path, "Cannot open temporary export file"));
		str = get_next_line(fd);
		while (str)
		{
			free(str);
			str = get_next_line(fd);
			length++;
		}
		close_and_free(fd, str);
	}
	free(path);
	return (length);
}

size_t	size_of_new_env(void)
{
	int		fd;
	char	*path;
	size_t	length;
	char	*str;

	length = 1;
	path = env_path();
	if (!path)
		return (0);
	if (access(path, F_OK) != -1)
	{
		fd = open(path, O_RDONLY, 0644);
		if (fd < 0)
			return (error_fd(path, "Cannot open temporary env file"));
		str = get_next_line(fd);
		while (str)
		{
			free(str);
			str = get_next_line(fd);
			length++;
		}
		close_and_free(fd, str);
	}
	free(path);
	return (length);
}
