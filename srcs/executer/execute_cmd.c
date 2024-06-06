/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:06:56 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/04/11 23:01:11 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**allocate_cmd(t_token **token)
{
	t_token	*tmp;
	int		len;
	char	**cmd;

	tmp = *token;
	len = 0;
	while (tmp && tmp->type != COMMAND)
		tmp = tmp->next;
	while (tmp && (tmp->type == COMMAND || tmp->type == ARGUMENT))
	{
		len++;
		tmp = tmp->next;
	}
	cmd = (char **)malloc(sizeof(char *) * (len + 1));
	if (!cmd)
		return (perror("Malloc "), NULL);
	return (cmd);
}

char	**get_cmd(t_pipeline *pipeline)
{
	t_token	*tmp;
	char	**cmd;
	int		i;

	tmp = pipeline->token;
	i = 0;
	cmd = allocate_cmd(&tmp);
	while (tmp && tmp->type != COMMAND)
		tmp = tmp->next;
	while (tmp && (tmp->type == COMMAND || tmp->type == ARGUMENT))
	{
		cmd[i] = ft_strdup(tmp->value);
		i++;
		tmp = tmp->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

void	execute_one(t_pipeline **pipeline, t_data *data, t_variable **variable)
{
	int		pid;
	char	**cmd;

	cmd = get_cmd((*pipeline));
	if (check_buildin(cmd, variable, (*pipeline), data->pipe_count))
		return (free_array(cmd));
	pid = fork();
	if (pid == 0)
	{
		handle_files(pipeline, 0);
		if ((*pipeline)->in_fd != -42)
			dup2((*pipeline)->in_fd, STDIN_FILENO);
		if ((*pipeline)->out_fd != -42)
			dup2((*pipeline)->out_fd, STDOUT_FILENO);
		ft_set_signals(cmd);
		execute(pipeline, (*data), 0, variable);
		exit(EXIT_FAILURE);
	}
	else
		ft_set_signals(cmd);
	waitpid(pid, &data->status, 0);
	reset_io(data->original_stdin, data->original_stdout);
	free_array(cmd);
}

int	execute(t_pipeline **pipeline, t_data data, int i, t_variable **variable)
{
	t_pipeline	*tmp;
	int			count;
	char		**cmd;
	char		*path;

	tmp = *pipeline;
	count = 0;
	while (count != i)
	{
		tmp = tmp->next;
		count++;
	}
	if (tmp->in_fd == -1 || tmp->out_fd == -1)
		return (1);
	cmd = get_cmd(tmp);
	ft_set_signals(cmd);
	if (check_buildin(cmd, variable, tmp, data.pipe_count))
		return (free_array(cmd), 0);
	path = get_path(tmp, variable);
	if (path != NULL)
		execve(path, cmd, data.envp);
	if (cmd[0])
		perror("Command not found ");
	return (free_array(cmd), free(path), 1);
}
