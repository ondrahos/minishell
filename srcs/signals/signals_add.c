/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daraz <daraz@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:18:49 by daraz             #+#    #+#             */
/*   Updated: 2024/04/23 09:18:49 by daraz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_sig_ignore(int sig)
{
	(void)sig;
}

void	ft_sig_heredoc(int sig)
{
	(void)sig;
	unlink("here_doc");
	exit(ER_MAIN);
}

void	ft_sig_empty(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	ft_set_signals(char **cmd)
{
	if (!cmd[0])
		return ;
	if (ft_strncmp(cmd[0], "./minishell", 10) == 0)
	{
		signal(SIGQUIT, ft_sig_ignore);
		signal(SIGINT, ft_sig_ignore);
	}
	if (ft_strncmp(cmd[0], "cat", 3) == 0)
	{
		signal(SIGINT, ft_c_handle_fork);
		signal(SIGQUIT, ft_slash_handle_fork);
	}
}
