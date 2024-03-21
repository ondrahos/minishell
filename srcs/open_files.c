/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:05:47 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/03/21 13:50:10 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* int	handle_files(t_pipeline **pipeline)
{
	t_pipeline	*tmp_pipe;
	t_token		*tmp_token;

	tmp_pipe = *pipeline;
	while (tmp_pipe)
	{
		tmp_token = tmp_pipe->token;
		while (tmp_token)
		{
			if (tmp_pipe->here_doc)
				tmp_pipe->in_fd = open_heredoc();
			else if (tmp_token->type == IN_FILE)
				tmp_pipe->in_fd
		}
	}
} */

