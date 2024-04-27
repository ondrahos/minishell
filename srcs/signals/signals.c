/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daraz <daraz@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:18:59 by daraz             #+#    #+#             */
/*   Updated: 2024/04/23 09:18:59 by daraz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_tty_mask(void)
{
	struct termios	sterm;

	tcgetattr(0, &sterm);
	sterm.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &sterm);
}

void	ft_c_handle(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_c_handle_fork(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	ft_slash_handle_fork(int sig)
{
	(void)sig;
	write(1, "Quit (core dumped)\n", 20);
}

void	ft_start_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_c_handle);
}
