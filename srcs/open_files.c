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

int	read_heredoc(t_pipeline *pipeline)
{
	char	*line;
	int		fd;

	line = NULL;
	fd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		perror("File ");
		return (1);
	}
	while (1)
	{
		line = readline("> ");
		if (line == NULL || ft_strncmp(line, pipeline->here_doc, ft_strlen(pipeline->here_doc)) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
		line = NULL;
	}
	free(line);
	close(fd);
	return (0);
}

int	open_heredoc(t_pipeline *pipeline)
{
	if (read_heredoc(pipeline) != 0)
	{
		perror("File ");
		return (1);
	}
	pipeline->in_fd = open("here_doc", O_RDONLY, 0777);
	if (pipeline->in_fd == -1)
	{
		perror("File ");
		return (1);
	}
	else
		return (0);
}

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

int	handle_files(t_pipeline **pipeline)
{
	t_pipeline	*tmp_pipe;
	t_token		*tmp_token;

	tmp_pipe = *pipeline;
	while (tmp_pipe)
	{
		tmp_token = tmp_pipe->token;
		if (tmp_pipe->here_doc != NULL)
		{
			if (open_heredoc(tmp_pipe) != 0)
				return (1);
		}
		while (tmp_token)
		{
			if (tmp_token->type == IN_FILE)
			{
				if (open_infile(tmp_pipe, tmp_token->value) != 0)
					return (1);
			}
			else if (tmp_token->type == OUT_FILE)
			{
				if (open_outfile(tmp_pipe, tmp_token->value) != 0)
					return (1);
			}
			tmp_token = tmp_token->next;
		}
		if (tmp_pipe->in_fd == -42)
			tmp_pipe->in_fd = STDIN_FILENO;
		if (tmp_pipe->out_fd == -42)
			tmp_pipe->out_fd = STDOUT_FILENO;
		tmp_pipe = tmp_pipe->next;
	}
	return (0);
}

