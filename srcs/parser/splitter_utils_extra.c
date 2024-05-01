/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter_utils_extra.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 19:44:53 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/04/26 16:09:27 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_token_length(char *s, int length, char quote)
{
	while (s[length] && !is_whitespace(s[length]))
	{
		if (is_quote(s[length]))
		{
			while(s[length] && is_quote(s[length]))
				quote = s[length++];
			while (s[length] && s[length] != quote)
				length++;
			if (s[length] == '\0')
				return (length);
			if (s[length] && is_quote(s[++length]))
				continue ;
			return (length);
		}
		else if (is_heredoc(s + length))
			return (2);
		else if (is_redir(s[length]))
			return (1);
		else
			length++;
		if (s[length] && s[length + 1] && is_redir(s[length + 1]))
			return (++length);
	}
	return (length);
}

int	count_tokens(char *s)
{
	int		i;
	int		tokens;
	int		token_length;
	char	quote;

	i = 0;
	tokens = 0;
	while (s[i])
	{
		quote = '\0';
		token_length = 0;
		while (s[i] && is_whitespace(s[i]))
			i++;
		if (s[i])
		{
			token_length = get_token_length(s + i, token_length, quote);
			if (token_length == -1)
				return (-1);
			tokens++;
			i += token_length;
		}
	}
	return (tokens);
}
