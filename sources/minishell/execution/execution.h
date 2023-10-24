/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 22:03:39 by dlacuey           #+#    #+#             */
/*   Updated: 2023/10/24 03:27:07 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

#include "parsing.h"

void	exec_full_command(t_node *node, int fds[3]);
void	exec_simple_command(char **value);
void	execution(t_node *node);

#endif
