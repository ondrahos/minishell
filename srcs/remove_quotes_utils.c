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

#include "../includes/minishell.h"

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

int	check_quotes(t_token *token)
{
	if (!token->value)
		return (0);
	if (has_quotes(token->value))
	{
		remove_quotes(token);
	}
	return (0);
}
