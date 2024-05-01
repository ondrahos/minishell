/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:03:20 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/03/27 17:04:44 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	has_quotes(char *s)
{
	int	i;


	i = 0;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
			return (true);
		i++;
	}
	return (false);
}

int	count_quotes(char *s)
{
	int	i;
	char	quote;

	i = 0;
	while (s[i])
	{
		quote = '\0';
		if (is_quote(s[i]))
		{
			quote = s[i++];
			while (s[i] && s[i] != quote)
				i++;
			if (s[i] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_quotes(t_token *token)
{
	if (!token->value)
		return (0);
	if (count_quotes(token->value) != 0)
		return (1);
	if (has_quotes(token->value))
	{
		remove_quotes(token);
	}
	return (0);
}
