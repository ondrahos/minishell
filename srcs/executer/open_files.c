/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:05:47 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/03/27 16:53:47 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_outfile(t_pipeline *pipeline, char *filename)
{
	if (pipeline->append == true)
		pipeline->out_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		pipeline->out_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (pipeline->in_fd == -1)
	{
		perror("File ");
		return (1);
	}
	else
		return (0);
}

int	open_infile(t_pipeline *pipeline, char *filename)
{
	pipeline->in_fd = open(filename, O_RDONLY, 0777);
	if (pipeline->in_fd == -1)
	{
		perror("File ");
		return (1);
	}
	else
		return (0);
}

int	proccess_files(t_token *tmp_token, t_pipeline *pipeline)
{
	if (tmp_token->type == HEREDOC)
	{
		if (open_heredoc(pipeline, tmp_token->next->value) != 0)
			return (1);
	}
	else if (tmp_token->type == IN_FILE)
	{
		if (open_infile(pipeline, tmp_token->value) != 0)
			return (1);
	}
	else if (tmp_token->type == OUT_FILE)
	{
		if (open_outfile(pipeline, tmp_token->value) != 0)
			return (1);
	}
	return (0);
}

int	handle_files(t_pipeline **pipeline, int i)
{
	t_token		*tmp_token;
	t_pipeline	*tmp_pipe;
	int			count;

	tmp_pipe = *pipeline;
	count = 0;
	while (count != i && tmp_pipe)
	{
		tmp_pipe = tmp_pipe->next;
		count++;
	}
	tmp_token = tmp_pipe->token;
	while (tmp_token)
	{
		proccess_files(tmp_token, tmp_pipe);
		tmp_token = tmp_token->next;
	}
	return (0);
}
