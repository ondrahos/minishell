/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 12:46:37 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/03/19 13:03:35 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*free_lines(char **s, int i)
{
	while (i >= 0)
	{
		free(s[i]);
		i--;
	}
	free(s);
	return (NULL);
}

bool	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

bool	is_redir(char c)
{
	return (c == '>' || c == '<');
}

bool	is_heredoc(char *s)
{
	return ((*s == '>' && *(s + 1) == '>') || (*s == '<' && *(s + 1) == '<'));
}

bool	is_delimiter(char *s)
{
	if (*s == ' ' || (*s >= 9 && *s <= 11))
		return (true);
	else if (*s == '>' || *s == '<')
		return (true);
	else if (*s == '\'' || *s == '\"')
		return (true);
	else
		return (false);
}
