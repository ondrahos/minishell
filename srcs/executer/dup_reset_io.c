/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_reset_io.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 19:52:48 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/04/26 16:07:56 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	dup_io(t_pipeline **pipeline, int i)
{
	t_pipeline	*tmp;
	int			count;

	tmp = *pipeline;
	count = 0;
	while (count != i)
	{
		tmp = tmp->next;
		count++;
	}
	if (tmp->in_fd >= 0)
		dup2(tmp->in_fd, STDIN_FILENO);
	if (tmp->out_fd >= 0)
		dup2(tmp->out_fd, STDOUT_FILENO);
}

void	reset_io(int original_stdin, int original_stdout)
{
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
}
