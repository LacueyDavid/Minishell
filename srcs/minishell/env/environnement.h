/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:06:07 by jdenis            #+#    #+#             */
/*   Updated: 2024/02/08 07:12:47 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONNEMENT_H
# define ENVIRONNEMENT_H

# include "colors.h"
# include "get_next_line.h"
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_envs
{
	char	**env;
	char	**exports;
}			t_envs;

t_envs		*copy_env_and_export(void);
void		free_envs(t_envs *envs);
void		update_envs(t_envs *envs);
char		*ft_strdup_with_quotes(char *str);
void		sort(char **exports);
char		**copy_environnement_from_file(int fd);
char		**copy_export_from_file(int fd);
void		update_export(t_envs *envs);
void		update_env(t_envs *envs);
char		*increased_shlvl(char *str);
char		**copy_environnement(void);
void		free_envs(t_envs *envs);
void		update_envs(t_envs *envs);
char		*env_path(void);
char		*exp_path(void);
size_t		size_of_new_exp(void);
size_t		size_of_new_env(void);
char		*get_line(char *str);
void		close_and_free(int fd, char *str);
void		inutile_return(char *path);
int			redo_env(char **input, size_t index, char ***env);
int			redo_export(char **input, size_t index, char ***env);
size_t		copy_underscore_var_env(char **new, size_t index);

#endif
