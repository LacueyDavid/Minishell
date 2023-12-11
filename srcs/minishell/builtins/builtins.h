/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 03:13:15 by jdenis            #+#    #+#             */
/*   Updated: 2023/12/11 13:15:27 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
#include <stddef.h>

typedef int (*builtin_func)(char **);

typedef struct {
    const char *command_name;
    builtin_func function;
} CommandMapping;

int		ft_echo(char *str);
int		ft_pwd(void);
int 	ft_cd(char *command);
int		ft_env(void);
int 	ft_exit(char *status);
int		ft_export(char **input);
int		ft_unset(char **input);
int		exec_builtin(char **command);
bool	is_a_builtin(char *command);

#endif