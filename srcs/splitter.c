/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:34:58 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/03/19 15:46:02 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_tokens(char *s)
{
	size_t		i;
	int			tokens;
	bool		inside_token;

	i = 0;
	tokens = 0;
	while (i < ft_strlen(s))
	{
		inside_token = false;
		while (s[i] && is_whitespace(s[i]))
			i++;
		while (s[i] && !is_whitespace(s[i]))
		{
			if (s[i] == '\'')
			{
				i++;
				while (s[i] && s[i] != '\'')
					i++;
				tokens++;
				i++;
				break ;
			}
			else if (s[i] == '\"')
			{
				i++;
				while (s[i] && s[i] != '\"')
					i++;
				tokens++;
				i++;
				break ;
			}
			else if (is_heredoc(s + i))
			{
				tokens++;
				i += 2;
				break ;
			}
			else if (is_redir(s[i]))
			{
				tokens++;
				i++;
				break ;
			}
			if (inside_token == false)
				tokens++;
			inside_token = true;
			i++;
		}
	}
	return (tokens);
}

char	**splitter(char *s)
{
	int		i;
	int		len;
	int		tokens;
	char	**ret;

	if (s == NULL)
		return (NULL);
	i = 0;
	tokens = count_tokens(s);
	ret = (char **)malloc((tokens + 1) * sizeof(char *));
	if (!ret)
	{
		perror("Malloc ");
		return (NULL);
	}
	ret[tokens] = NULL;
	while (i < tokens)
	{
		len = 0;
		while (*s && is_whitespace(*s))
			s++;
		if (s[len] == '\'')
		{
			len++;
			while (s[len] && s[len] != '\'')
				len++;
			len++;
		}
		else if (s[len] == '\"')
		{
			len++;
			while (s[len] && s[len] != '\"')
				len++;
			len++;
		}
		else if (is_heredoc(&s[len]))
			len += 2;
		else if (is_redir(s[len]))
			len++;
		else
		{
			while (s[len] && !is_delimiter(&s[len]))
				len++;
		}
		ret[i] = ft_substr(s, 0, len);
		if (!ret[i])
			return (free_lines(ret, i));
		s += len;
		i++;
	}
	return (ret);
}