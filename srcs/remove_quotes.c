/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:53:53 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/03/20 14:08:47 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_quotes(t_token *token)
{
	char	*tmp;

	tmp = ft_substr(token->value, 1, ft_strlen(token->value) - 2);
	if (tmp == NULL)
	{
		perror("Malloc ");
		return ;
	}
	if (token->free == true)
		free(token->value);
	token->value = tmp;
	token->free = true;
}

int	check_quotes(t_token *token)
{
	if (!token->value)
		return (0);
	if (token->value[0] == '\"')
	{
		if (token->value[ft_strlen(token->value) - 1] != '\"')
			return (1);
		remove_quotes(token);
	}
	else if (token->value[0] == '\'')
	{
		if (token->value[ft_strlen(token->value) - 1] != '\'')
			return (1);
		remove_quotes(token);
	}
	return (0);
}

int	handle_quotes(t_pipeline **pipeline)
{
	t_pipeline	*tmp_pipe;
	t_token		*tmp_token;

	tmp_pipe = *pipeline;
	while (tmp_pipe)
	{
		tmp_token = tmp_pipe->token;
		while (tmp_token)
		{
			if (check_quotes(tmp_token) != 0)
				return (1);
			tmp_token = tmp_token->next;
		}
		tmp_pipe = tmp_pipe->next;
	}
	return (0);
}

