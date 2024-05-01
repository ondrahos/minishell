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

#include "../../includes/minishell.h"

int	check_rest(char *s, int *len)
{
	if (is_heredoc(s + (*len)))
	{
		(*len) += 2;
		return (1);
	}
	else if (is_redir(s[(*len)]))
	{
		(*len)++;
		return (1);
	}
	else
	{
		(*len)++;
		return (0);
	}
}

char	*extract_token(char *s, char **ret, int len, char quote)
{
	while (s[len] && !is_whitespace(s[len]))
	{
		if (is_quote(s[len]))
		{
			while (s[len] && is_quote(s[len]))
				quote = s[len++];
			while (s[len] && s[len] != quote)
				len++;
			if (s[len] == '\0')
				break ;
			if (is_quote(s[++len]))
				continue ;
			break ;
		}
		if (check_rest(s, &len) == 1)
			break ;
		if (s[len] && s[len + 1] && is_redir(s[len + 1])
			&& !is_whitespace(s[len]))
		{
			len++;
			break ;
		}
	}
	*ret = ft_substr(s, 0, len);
	if (!(*ret))
		return (NULL);
	return (s + len);
}

void	extract_tokens(char **ret, char *s, int tokens)
{
	int		i;
	char	*token_end;
	int		len;
	char	quote;

	i = 0;
	while (i < tokens)
	{
		len = 0;
		quote = '\0';
		while (*s && is_whitespace(*s))
			s++;
		token_end = extract_token(s, &ret[i], len, quote);
		if (!token_end)
		{
			free_lines(ret, i);
			return ;
		}
		s = token_end;
		i++;
	}
}

char	**allocate_ret(int tokens)
{
	char	**ret;

	ret = (char **)malloc((tokens + 1) * sizeof(char *));
	if (!ret)
	{
		perror("Malloc ");
		return (NULL);
	}
	ret[tokens] = NULL;
	return (ret);
}

char	**splitter(char *s)
{
	char	**ret;
	int		tokens;

	tokens = 0;
	if (s == NULL)
		return (NULL);
	tokens = count_tokens(s);
	ret = allocate_ret(tokens);
	if (!ret)
	{
		perror("Malloc ");
		return (NULL);
	}
	extract_tokens(ret, s, tokens);
	return (ret);
}
