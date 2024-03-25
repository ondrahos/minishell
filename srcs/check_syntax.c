/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:20:25 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/03/22 16:33:06 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_pipes(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '|' && line[i + 1] == '|')
			{
				ft_putendl_fd("Syntax error: Invalid syntax near: \"|\"", STDERR_FILENO);
				return (1);
			}
		else if (line[i] == '|' && line[i + 1] == '\0')
			{
				ft_putendl_fd("Syntax error: Invalid syntax near: \"|\"", STDERR_FILENO);
				return (1);
			}
		i++;
	}
	return (0);
}

bool	is_invalid(t_type next)
{
	return (next == R_IN || next == R_OUT || next == APPEND || next == HEREDOC);
}

int	check_syntax(t_pipeline **pipeline)
{
	t_pipeline	*tmp_pipe;
	t_token		*tmp_token;

	tmp_pipe = *pipeline;
	while (tmp_pipe)
	{
		tmp_token = tmp_pipe->token;
		while (tmp_token)
		{
			if (tmp_token->type == R_IN && is_invalid(tmp_token->next->type))
			{
				ft_putendl_fd("Syntax error: Invalid syntax near: \"<\"", STDERR_FILENO);
				return (1);
			}
			else if (tmp_token->type == R_OUT && is_invalid(tmp_token->next->type))
			{
				ft_putendl_fd("Syntax error: Invalid syntax near: \">\"", STDERR_FILENO);
				return (1);
			}
			else if (tmp_token->type == APPEND && is_invalid(tmp_token->next->type))
			{
				ft_putendl_fd("Syntax error: Invalid syntax near: \">>\"", STDERR_FILENO);
				return (1);
			}
			else if (tmp_token->type == HEREDOC && is_invalid(tmp_token->next->type))
			{
				ft_putendl_fd("Syntax error: Invalid syntax near: \"<<\"", STDERR_FILENO);
				return (1);
			}
			tmp_token = tmp_token->next;
		}
		tmp_pipe = tmp_pipe->next;
	}
	return (0);
}
