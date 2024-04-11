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
	cmd = get_cmd(tmp);
	path = get_path(tmp, variable);
	execve(path, cmd, data.envp);
	perror("Exec ");
	return (0);
}
