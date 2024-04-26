/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:49:47 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/03/27 16:50:19 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	read_heredoc(char *eof)
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
	signal(SIGINT, ft_sig_heredoc);
	while (1)
	{
		line = readline("> ");
		if (line == NULL || ft_strncmp(line, eof, ft_strlen(eof)) == 0)
			break ;
		ft_putendl_fd(line, fd);
		free(line);
		line = NULL;
	}
	free(line);
	close(fd);
	return (0);
}

int	open_heredoc(t_pipeline *pipeline, char *eof)
{
	if (read_heredoc(eof) != 0)
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
