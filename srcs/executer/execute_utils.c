/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 19:46:31 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/04/26 16:08:11 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	*allocate_pids(int pipeline_count)
{
	int	*ret;

	ret = (int *)malloc(sizeof(int) * pipeline_count);
	if (!ret)
		return (perror("Malloc "), NULL);
	return (ret);
}

int	**allocate_pipes(int pipeline_count)
{
	int	**ret;
	int	i;

	i = 0;
	ret = (int **)malloc(pipeline_count * sizeof(int *));
	if (!ret)
		return (perror("Malloc "), NULL);
	while (i < pipeline_count)
	{
		ret[i] = (int *)malloc(sizeof(int) * 2);
		if (!ret[i])
			return (perror("Malloc "), NULL);
		i++;
	}
	return (ret);
}

int	count_pipes(t_pipeline **pipeline)
{
	t_pipeline	*tmp;
	int			count;

	tmp = *pipeline;
	count = 0;
	while (tmp->next)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

void	data_init(t_data *data, char **envp, t_pipeline **pipeline)
{
	data->pipe_count = count_pipes(pipeline);
	data->pipes = allocate_pipes(data->pipe_count);
	data->pids = allocate_pids(data->pipe_count + 1);
	data->envp = envp;
	data->original_stdin = dup(STDIN_FILENO);
	data->original_stdout = dup(STDOUT_FILENO);
	data->status = 0;
}

int	safe_fork(t_data *data, int i)
{
	if (data->pids[i] < 0)
	{
		close_pipes(data->pipes, data->pipe_count);
		free_data(data);
		perror("Fork ");
		return (-1);
	}
	return (0);
}
