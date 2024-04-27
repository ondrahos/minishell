/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:35:34 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/03/27 16:43:23 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_token(t_token *token)
{
	token->type = 0;
	token->value = NULL;
	token->free = false;
	token->next = NULL;
}

t_token	*new_token(void)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
	{
		perror("Malloc ");
		return (NULL);
	}
	init_token(new);
	return (new);
}

void	load_token(char **line, t_token **token)
{
	t_token	*tmp;
	int		i;

	i = 0;
	*token = new_token();
	tmp = *token;
	while (line[i])
	{
		tmp->value = line[i];
		if (line[i + 1])
			tmp->next = new_token();
		tmp = tmp->next;
		i++;
	}
}

void	proccess_redirections(t_token *tmp, t_pipeline *pipeline,
								char **line, int i)
{
	if (ft_strncmp(line[i], "<", 2) == 0)
		tmp->type = R_IN;
	else if (ft_strncmp(line[i], ">", 2) == 0)
		tmp->type = R_OUT;
	else if (ft_strncmp(line[i], ">>", 3) == 0)
	{
		tmp->type = APPEND;
		pipeline->append = true;
	}
	else if (ft_strncmp(line[i], "<<", 3) == 0)
	{
		tmp->type = HEREDOC;
		pipeline->here_doc = true;
	}
	else if (i > 0 && ft_strncmp(line[i - 1], "<<", 3) == 0)
		tmp->type = DELIMITER;
	else if (i > 0 && ft_strncmp(line[i - 1], "<", 2) == 0)
		tmp->type = IN_FILE;
	else if ((i > 0 && ft_strncmp(line[i - 1], ">", 2) == 0)
		|| (i > 0 && ft_strncmp(line[i - 1], ">>", 3) == 0))
	{
		tmp->type = OUT_FILE;
		if (i > 0 && ft_strncmp(line[i - 1], ">", 2) == 0)
			pipeline->append = false;
	}
}

void	assign_type(char **line, t_token **token, t_pipeline *pipeline)
{
	t_token	*tmp;
	int		i;
	bool	cmd;

	i = 0;
	tmp = *token;
	cmd = false;
	while (tmp && line[i])
	{
		proccess_redirections(tmp, pipeline, line, i);
		if (tmp->type == 0)
		{
			if (cmd == true)
				tmp->type = ARGUMENT;
			else
			{
				tmp->type = COMMAND;
				cmd = true;
			}
		}
		tmp = tmp->next;
		i++;
	}
}
