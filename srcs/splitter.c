/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:34:58 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/03/27 17:42:07 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	get_token_length(char *s)
{
	int		length;
	char	quote;

	length = 0;
	quote = '\0';
    while (s[length] && !is_whitespace(s[length]))
	{
		if (s[length] == '\'' || s[length] == '\"')
		{
			quote = s[length++];
			while (s[length] && s[length] != quote)
				length++;
			if (s[length] == '\0')
				return (0);
			if (s[length] && is_quote(s[++length]))
				continue ;
		}
		else if (is_heredoc(s + length))
			return (2) ;
		else if (is_redir(s[length]))
			return (1) ;
		else
			length++;
		if (s[length] && s[length + 1] && (is_heredoc(&s[length + 1]) || is_redir(s[length + 1])))
			{
				length++;
				break ;
			}
	}
	return (length);
}

int count_tokens(char *s)
{
	size_t 	i;
	int 	tokens;
	int		token_length;

	i  = 0;
	tokens = 0;
	token_length = 0;
	while (s[i])
	{
		while (s[i] && is_whitespace(s[i]))
			i++;
		if (s[i])
		{
			token_length = get_token_length(s + i);
			if (token_length == 0)
				return (-1);
			tokens++;
			i += token_length;
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
	char	quote;

	if (s == NULL)
		return (NULL);
	i = 0;
	quote = '\0';
	tokens = count_tokens(s);
	if (tokens == -1)
	{
		ft_putendl_fd("Syntax error: Unclosed quotes", STDERR_FILENO);
		return (NULL);
	}
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
		while (s[len] && !is_whitespace(s[len]))
		{
			if (is_quote(s[len]))
			{
				quote = s[len++];
				while (s[len] && s[len] != quote)
					len++;
				if (is_quote(s[++len]))
					continue ;
			}
			else if (is_heredoc(s + len))
			{
				len += 2;
				break ;
			}
			else if (is_redir(s[len]))
			{
				len++;
				break ;
			}
			else
				len++;
			if (s[len] && s[len + 1] && (is_heredoc(s + len + 1) || is_redir(s[len + 1])))
			{
				len++;
				break ;
			}
		}
		ret[i] = ft_substr(s, 0, len);
		if (!ret[i])
			return (free_lines(ret, i));
		s += len;
		i++;
	}
	return (ret);
}
