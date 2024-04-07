/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:06:56 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/04/07 14:59:53 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_all_pipes(int **pipes, int num)
{
	int	i;

	i = 0;
	while (i <= num)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	close_pipes(t_data data, int pos)
{
	int	i;

	i = 0;
	if (pos == 0)
	{
		while (i < data.pipeline_count)
		{
			close(data.pipes[i][0]);
			if (i != pos)
				close(data.pipes[i][1]);
			i++;
		}
	}
	else if (pos == data.pipeline_count)
	{
		while (i < data.pipeline_count)
		{
			close(data.pipes[i][1]);
			if (i != pos - 1)
				close(data.pipes[i][0]);
			i++;
		}
	}
	else
	{
		while (i < data.pipeline_count)
		{
			if (i != pos - 1)
				close(data.pipes[i][0]);
			if (i != pos)
				close(data.pipes[i][1]);
			i++;
		}
	}
}

int	*allocate_pids(int pipeline_count)
{
	int*ret;

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
	while(i < pipeline_count)
	{
		ret[i] = (int *)malloc(sizeof(int) * 2);
		if (!ret[i])
			return (perror("Malloc "), NULL);
		i++;
	}
	return (ret);
}

int	count_pipelines(t_pipeline **pipeline)
{
	t_pipeline	*tmp;
	int			count;

	tmp = *pipeline;
	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

char	**allocate_cmd(t_token **token)
{
	t_token	*tmp;
	int		len;
	char	**cmd;

	tmp = *token;
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

char	*find_path(t_token *token, char *path_var)
{
	char	**paths;
	int		i;
	char	*path;
	char	*slashed;

	if (ft_strchr(token->value, '/'))
	{
		if (access(token->value, F_OK) == 0)
			return (ft_strdup(token->value));
		token->type = COMMAND_ERR_PATH;
		return (NULL);
	}
	i = 0;
	paths = ft_split(path_var, ':');
	while (paths[i])
	{
		slashed = ft_strjoin(paths[i], "/");
		path = ft_strjoin(slashed, token->value);
		free(slashed);
		if (access(path, F_OK) == 0)
		{
			free_array(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free(path);
	free_array(paths);
	token->type = COMMAND_ERR;
	return (NULL);
}

char	*get_path(t_pipeline *pipeline, t_variable **variable)
{
	char		*path;
	t_token		*tmp_token;
	t_variable	*tmp_var;

	tmp_token = pipeline->token;
	tmp_var = *variable;
	while (tmp_var && ft_strncmp(tmp_var->name, "PATH", 5) != 0)
		tmp_var = tmp_var->next;
	while (tmp_token && tmp_token->type != COMMAND)
		tmp_token = tmp_token->next;
	path = find_path(tmp_token, tmp_var->value);
	return (path);
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
	if (handle_files(pipeline) != 0)
		return (1);
	cmd = get_cmd(tmp);
	path = get_path(tmp, variable);
	dup2(tmp->in_fd, STDIN_FILENO);
	dup2(tmp->out_fd, STDOUT_FILENO);
	if (i == 0)
	{
		dup2(data.pipes[i][1], STDOUT_FILENO);
		close(data.pipes[i][1]);
	}
	else if (i == data.pipeline_count)
	{
		dup2(data.pipes[i - 1][0], STDIN_FILENO);
		close(data.pipes[i - 1][0]);
	}
	else
	{
		dup2(data.pipes[i - 1][0], STDIN_FILENO);
		dup2(data.pipes[i][1], STDOUT_FILENO);
		close(data.pipes[i - 1][0]);
		close(data.pipes[i][1]);
	}
	execve(path, cmd, data.envp);
	perror("Exec ");
	return (0);
}
