/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:20:25 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/03/27 13:09:53 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_pipes(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '|' && line[i + 1] == '|')
		{
			ft_putendl_fd("Syntax error: Invalid syntax near: \"|\"",
				STDERR_FILENO);
			return (1);
		}
		else if (line[i] == '|' && line[i + 1] == '\0')
		{
			ft_putendl_fd("Syntax error: Invalid syntax near: \"|\"",
				STDERR_FILENO);
			return (1);
		}
		i++;
	}
	return (0);
}

bool	is_invalid(t_token *next)
{
	if (!next)
		return (true);
	else if (next->type == R_IN || next->type == R_OUT
		|| next->type == APPEND || next->type == HEREDOC)
		return (true);
	else
		return (false);
}

void	print_msg(int code)
{
	if (code == R_IN)
		ft_putendl_fd("Syntax error: Invalid syntax near: \"<\"",
			STDERR_FILENO);
	else if (code == R_OUT)
		ft_putendl_fd("Syntax error: Invalid syntax near: \">\"",
			STDERR_FILENO);
	else if (code == APPEND)
		ft_putendl_fd("Syntax error: Invalid syntax near: \">>\"",
			STDERR_FILENO);
	else if (code == HEREDOC)
		ft_putendl_fd("Syntax error: Invalid syntax near: \"<<\"",
			STDERR_FILENO);
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
			if (tmp_token->type == R_IN && is_invalid(tmp_token->next))
				return (print_msg(R_IN), 1);
			else if (tmp_token->type == R_OUT && is_invalid(tmp_token->next))
				return (print_msg(R_OUT), 1);
			else if (tmp_token->type == APPEND && is_invalid(tmp_token->next))
				return (print_msg(APPEND), 1);
			else if (tmp_token->type == HEREDOC && is_invalid(tmp_token->next))
				return (print_msg(HEREDOC), 1);
			tmp_token = tmp_token->next;
		}
		tmp_pipe = tmp_pipe->next;
	}
	return (0);
}
