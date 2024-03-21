/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:19:30 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/03/20 16:31:25 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* void	close_files(t_pipeline *pipeline)
{
	if (pipeline->in_fd != STDIN_FILENO)
		close(pipeline->in_fd);
	if (pipeline->out_fd != STDOUT_FILENO)
		close(pipeline->out_fd);
}
 */
void	free_variable(t_variable **variable)
{
	t_variable	*tmp;

	tmp = *variable;
	while (tmp)
	{
		free((*variable)->name);
		(*variable)->name = NULL;
		free((*variable)->value);
		(*variable)->value = NULL;
		tmp = (*variable)->next;
		free(*variable);
		*variable = tmp;
	}
	*variable = NULL;
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
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
	while(*token)
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
		/* close_files(*pipeline); */
		free_tokens(&(*pipeline)->token);
		tmp = (*pipeline)->next;
		free(*pipeline);
		*pipeline = tmp;
	}
	*pipeline = NULL;
}
