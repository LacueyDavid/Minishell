/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signals.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 17:21:00 by dlacuey           #+#    #+#             */
/*   Updated: 2024/01/25 15:13:18 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_SIGNALS_H
# define MINISHELL_SIGNALS_H

void	handler_sigquit(int sig);
void	handler_sigint_main(int sig);
void	handler_sigint(int sig);
void	handle_heredoc(int sig);

#endif
