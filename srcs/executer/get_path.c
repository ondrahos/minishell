/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 19:49:27 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/05/09 18:28:52 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_absolute_path(t_token *token)
{
	if (access(token->value, F_OK) == 0)
		return (ft_strdup(token->value));
	return (NULL);
}

char	*find_relative_path(t_token *token, char *path_var)
{
	char	**paths;
	char	*path;
	char	*slashed;
	int		i;

	paths = ft_split(path_var, ':');
	i = 0;
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

char	*find_path(t_token *token, char *path_var)
{
	if (!token)
		return (NULL);
	if (ft_strchr(token->value, '/'))
		return (find_absolute_path(token));
	return (find_relative_path(token, path_var));
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
	if (!tmp_var)
		return (NULL);
	while (tmp_token && tmp_token->type != COMMAND)
		tmp_token = tmp_token->next;
	path = find_path(tmp_token, tmp_var->value);
	return (path);
}
