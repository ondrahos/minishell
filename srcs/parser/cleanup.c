/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:19:30 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/03/26 16:19:15 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_files(t_pipeline *pipeline)
{
	if (pipeline->here_doc)
		unlink("here_doc");
	if (pipeline->in_fd != STDIN_FILENO && pipeline->in_fd > 0)
		close(pipeline->in_fd);
	if (pipeline->out_fd != STDOUT_FILENO && pipeline->out_fd > 0)
		close(pipeline->out_fd);
}

void	free_variable(t_variable **variable)
{
	t_variable	*tmp;

	if (!variable || !(*variable))
		return ;
	tmp = *variable;
	while (tmp)
	{
		tmp = (*variable)->next;
		free((*variable)->name);
		(*variable)->name = NULL;
		free((*variable)->value);
		(*variable)->value = NULL;
		free(*variable);
		*variable = tmp;
	}
	*variable = NULL;
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		if (arr[i] != NULL)
			free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_tokens(t_token **token)
{
	t_token	*tmp;

	if (!token || !(*token))
		return ;
	while (*token)
	{
		if ((*token)->free == true)
		{
			free((*token)->value);
			(*token)->value = NULL;
		}
		tmp = (*token)->next;
		free(*token);
		*token = tmp;
	}
	*token = NULL;
}

void	free_pipeline(t_pipeline **pipeline)
{
	t_pipeline	*tmp;

	if (!pipeline || !(*pipeline))
		return ;
	while (*pipeline)
	{
		free_array((*pipeline)->line);
		close_files(*pipeline);
		free_tokens(&(*pipeline)->token);
		tmp = (*pipeline)->next;
		free(*pipeline);
		*pipeline = tmp;
	}
	*pipeline = NULL;
}
