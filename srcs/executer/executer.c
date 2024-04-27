/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 19:57:10 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/04/26 20:39:29 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	setup_child_io(t_data *data, t_pipeline **pipeline, int index)
{
	dup_io(pipeline, index);
	if (index != data->pipe_count)
		dup2(data->pipes[index][1], STDOUT_FILENO);
	if (index != 0)
		dup2(data->pipes[index - 1][0], STDIN_FILENO);
}

int	fork_processes(t_data *data, t_pipeline **pipeline, t_variable **variable)
{
	int	i;

	i = 0;
	while (i < data->pipe_count + 1)
	{
		data->pids[i] = fork();
		if (safe_fork(data, i) == -1)
			return (-1);
		if (data->pids[i] == 0)
		{
			handle_files(pipeline, i);
			setup_child_io(data, pipeline, i);
			close_pipes(data->pipes, data->pipe_count);
			free_data(data);
			execute(pipeline, *data, i, variable);
			exit(EXIT_FAILURE);
		}
		else
		{
			signal(SIGQUIT, ft_sig_ignore);
			signal(SIGINT, ft_sig_ignore);
		}
		i++;
	}
	return (0);
}

void	wait_for_children(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->pipe_count + 1)
	{
		waitpid(data->pids[i], &data->status, 0);
		i++;
	}
}

int	setup_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->pipe_count)
	{
		if (pipe(data->pipes[i]) < 0)
		{
			close_pipes(data->pipes, i);
			free_data(data);
			perror("Pipe ");
			return (-1);
		}
		i++;
	}
	return (0);
}

void	executer(t_pipeline **pipeline, t_variable **variable, char **envp)
{
	t_data	data;

	data_init(&data, envp, pipeline);
	if (data.pipe_count == 0)
	{
		free_data(&data);
		execute_one(pipeline, &data, variable);
		check_pipeline_status(&data, pipeline);
		update_status(data.status, variable);
		return ;
	}
	if (setup_pipes(&data) != 0)
		return ;
	if (fork_processes(&data, pipeline, variable) != 0)
		return ;
	close_pipes(data.pipes, data.pipe_count);
	wait_for_children(&data);
	reset_io(data.original_stdin, data.original_stdout);
	check_pipeline_status(&data, pipeline);
	update_status(data.status, variable);
	free_data(&data);
}
