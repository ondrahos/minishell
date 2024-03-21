/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:33:57 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/01/15 14:35:41 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_line(int fd, char *buffer, char *next_call)
{
	int		read_line;
	char	*temp;

	read_line = 1;
	while (read_line != 0)
	{
		read_line = read(fd, buffer, BUFFER_SIZE);
		if (read_line == -1)
			return (NULL);
		else if (read_line == 0)
			break ;
		buffer[read_line] = '\0';
		if (!next_call)
			next_call = ft_strdup("");
		temp = next_call;
		next_call = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (next_call);
}

static char	*extract(char *line)
{
	size_t	i;
	char	*str;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0' || line[1] == '\0')
		return (NULL);
	str = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*str == '\0')
	{
		free(str);
		str = NULL;
	}
	line[i + 1] = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*next_call;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	line = get_line(fd, buffer, next_call);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	next_call = extract(line);
	return (line);
}
