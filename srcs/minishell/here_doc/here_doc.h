/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 17:35:20 by dlacuey           #+#    #+#             */
/*   Updated: 2023/12/07 17:38:54 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_H
# define HERE_DOC_H

#include "execution.h"

void	fill_heredocs(t_node *node, int fds[NUMBER_OF_FDS]);
void	fork_heredocs(t_node *node, int fds[NUMBER_OF_FDS]);
void	unlink_heredoc_files(t_node *node);
size_t	how_many_heredocs(t_node *node);
void	here_doc(t_node *node);

#endif
