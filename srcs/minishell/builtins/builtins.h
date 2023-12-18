/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 03:13:15 by jdenis            #+#    #+#             */
/*   Updated: 2023/12/13 17:09:13 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <stddef.h>
# include "environnement.h"

int		ft_echo(char *str);
int		ft_pwd(t_envs *envs);
int 	ft_cd(t_envs *envs, char *command);
int		ft_env(t_envs *envs);
int 	ft_exit(char *status);
int		ft_export(t_envs *envs, char **input);
int		ft_unset(t_envs *envs, char **input);
int		exec_builtin(char **command, t_envs *envs);
bool	is_a_builtin(char *command);
char    *ft_getenv(char *name, t_envs *envs);

#endif