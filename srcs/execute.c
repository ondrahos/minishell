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
	while (i < num)
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
	free_array(paths);
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

void	dup_io(t_pipeline **pipeline, int i)
{
	t_pipeline	*tmp;
	int			count;

	tmp = *pipeline;
	count = 0;
	while (count != i)
	{
		tmp = tmp->next;
		count++;
	}
	if (tmp->in_fd >= 0)
		dup2(tmp->in_fd, STDIN_FILENO);
	if (tmp->out_fd >= 0)
		dup2(tmp->out_fd, STDOUT_FILENO);
}

// void	reset_io(int original_stdin, int original_stdout)
// {
// 	dup2(original_stdin, STDIN_FILENO);
// 	dup2(original_stdout, STDOUT_FILENO);
// 	close(original_stdin);
// 	close(original_stdout);
// }

void	execute_one(t_pipeline **pipeline, t_data data, t_variable **variable)
{
	int	pid;
	int	original_stdin = dup(STDIN_FILENO);
	int	original_stdout = dup(STDOUT_FILENO);

	pid = fork();
	if (pid == 0)
	{
		if ((*pipeline)->in_fd != -42)
			dup2((*pipeline)->in_fd, STDIN_FILENO);
		if ((*pipeline)->out_fd != -42)
			dup2((*pipeline)->out_fd, STDOUT_FILENO);
		execute(pipeline, data, 0, variable);
		exit(EXIT_FAILURE);
	}
	wait(NULL);
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
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
	path = get_path(tmp, variable);
	if (path != NULL)
		execve(path, cmd, data.envp);
	perror("Exec ");
	free_array(cmd);
	free(path);
	return (1);
}
