/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:11:18 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/03/27 17:21:09 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_alphanum(char c)
{
	if ((c <= 'Z' && c >= 'A') || (c <= 'z' && c >= 'a')
		|| (c >= '0' && c <= '9') || c == '_')
		return (true);
	return (false);
}

bool	is_in_squotes(char *s, int position)
{
	int		i;
	bool	found;
	char	quote;

	i = 0;
	found = false;
	while (s[i])
	{
		if (is_quote(s[i]))
		{
			quote = s[i];
			i++;
			while (s[i] && s[i] != quote)
			{
				if (i == position)
					found = true;
				i++;
			}
			if (s[i] != '\0' && found == true && quote == '\'')
				return (true);
		}
		if (s[i])
			i++;
	}
	return (false);
}

bool	is_var(char *value)
{
	int	i;

	i = 0;
	if (!value)
		return (false);
	while (value[i])
	{
		if (value[i] == '$')
		{
			if (is_in_squotes(value, i) == false)
				return (true);
		}
		i++;
	}
	return (false);
}

bool	is_whitespace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

void	replace_value(char *tmp, t_token *token, bool free_var, char *var)
{
	if (free_var == true)
		free(token->value);
	token->value = tmp;
	token->free = true;
	if (var)
	{
		free(var);
		var = NULL;
	}
}
