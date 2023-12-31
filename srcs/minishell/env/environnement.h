/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:06:07 by jdenis            #+#    #+#             */
/*   Updated: 2023/12/18 16:03:44 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONNEMENT_H
# define ENVIRONNEMENT_H

typedef struct s_envs
{
	char			**env;
	char			**exports;
}					t_envs;

t_envs	*copy_env_and_export(void);
void	free_envs(t_envs *envs);
void	redo_envs(t_envs *envs);
void	update_envs(t_envs *envs);
char	*ft_strdup_with_quotes(char *str);

#endif
