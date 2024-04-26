/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env_syntax.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:25:26 by daraz             #+#    #+#             */
/*   Updated: 2024/04/23 20:22:29 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	starts_with_correct_char(char *value)
{
	if (value && (ft_isalpha(value[0]) || value[0] == '_'))
		return (true);
	else
		return (false);
}

static bool	valid_chars(char *value)
{
	int	i;

	i = 0;
	while (value[i] != '\0' && value[i] != '=')
	{
		if (ft_isalnum(value[i]) || value[i] == '_')
			i++;
		else
			return (false);
	}
	return (true);
}

bool	ft_check_env_syntax(char *value)
{
	if (!starts_with_correct_char(value) || !valid_chars(value))
		return (false);
	else
		return (true);
}
