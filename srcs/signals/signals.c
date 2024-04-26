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

/* tady potrebujeme prenastavit terminal I/O controls.
Kdyz se bude mackat ctrl+c tak by se nemelo printit do obrazovky.
my vypnutim echo control zamezime abychom videli co mackame do terminalu.
melo by to byt obsazeno v main loopu behu minishellu stejne jako start signals
*/
void	ft_tty_mask(void)
{
	struct termios	sterm;

	tcgetattr(0, &sterm);
	sterm.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &sterm);
}

/* toto bude nas handler na ctrl+c (Interrupt process)
informujeme terminal ze bude novy radek, smazeme vsechno prazdnym stringem
a updatneme ho aby to ukazoval*/
void	ft_c_handle(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/* neco takoveho bych dal jako handler primo na child processy po forkovani*/
void	ft_c_handle_fork(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

/* toto je handler pro ctrl + \ signal (terminate process SIGQUIT)*/
void	ft_slash_handle_fork(int sig)
{
	(void)sig;
	write(1, "Quit (core dumped)\n", 20);
}

/* jelikoz mame minishell v shellu tak musime zamezit aby nam ctrk+c vypnulo
nas minishell :D takze odchytime signal QUIT a ignorujeme ho IGN
nasledne spustime handler s parametrem nasi funkce na ctrl + c,
pravdepodobne pred dalsim loopem bude treba to dat znovu protoze ty signaly behem running shell muzeme zmenit*/
void	ft_start_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_c_handle);
}


/* bude treba udelat funkci nanastaveni signalu podle argumentu
neco ve smyslu */
void	ft_set_signals(char **cmd)
{
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
/*
cat a heredoc me napadaji jako jediny kdy pobezi ten process
bude treba to dat nekam pred vidlici executu binu, protoze tam uz bude treba
zaznamenavat zmeny, protoze na rozdil od build inu, tam jsou defaultni nastaveni */
