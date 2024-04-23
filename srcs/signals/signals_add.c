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

#include "../buildins/build.h"

/* tady asi neni moc co vysvetlovat... do nothing...*/
void	ft_sig_ignore(int sig)
{
	(void)sig;
}

/* tady prave az budeme cekat na input behem here docku
a zmackneme ctrl+c, bude treba zpracovat aby jenom exitnul here doc
signal(SIGINT, ft_sig_heredoc);  */
void	ft_sig_heredoc(int sig)
{
	(void)sig;
	exit(ER_MAIN);
}

void	ft_sig_empty(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}