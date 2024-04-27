/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daraz <daraz@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 10:38:02 by daraz             #+#    #+#             */
/*   Updated: 2024/04/27 11:06:56 by daraz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_old_path(t_pipeline *pipeline,
	t_variable **envs, char *old_path)
{
	char	**old_pwd;

	old_pwd = malloc(sizeof(char *) * 3 + 1);
	if (old_pwd == NULL)
		ft_malloc_error();
	old_pwd[2] = NULL;
	ft_remove_env_var(envs, "OLDPWD");
	old_pwd[0] = ft_strdup("export");
	old_pwd[1] = ft_strjoin("OLDPWD=", old_path);
	if (old_pwd == NULL)
		ft_malloc_error();
	ft_export(pipeline, envs, old_pwd);
	free_array(old_pwd);
}

static void	update_new_path(t_pipeline *pipeline,
	t_variable **envs, char *new_path)
{
	char	**new_pwd;

	new_pwd = malloc(sizeof(char *) * 3 + 1);
	if (new_pwd == NULL)
		ft_malloc_error();
	new_pwd[2] = NULL;
	ft_remove_env_var(envs, "PWD");
	new_pwd[0] = ft_strdup("export");
	new_pwd[1] = ft_strjoin("PWD=", new_path);
	if (new_pwd == NULL)
		ft_malloc_error();
	ft_export(pipeline, envs, new_pwd);
	free_array(new_pwd);
}

static void	update_paths(t_pipeline *pipeline, t_variable **envs,
	char *old_path, char *new_path)
{
	update_old_path(pipeline, envs, old_path);
	update_new_path(pipeline, envs, new_path);
}

void	ft_cd(t_pipeline *pipeline, t_variable **envs, char **cmd)
{
	char	old_path[PATH_MAX + 1];
	char	new_path[PATH_MAX + 1];
	char	*status;

	status = getcwd(old_path, PATH_MAX + 1);
	if (status == NULL)
		ft_path_error();
	if (cmd[1] == NULL)
	{
		if (ft_handle_empty_path(pipeline, envs) == false)
			return ;
	}
	else
	{
		if (chdir(cmd[1]) == -1)
			return (ft_handle_invalid_path(pipeline, envs, cmd[1]));
	}
	status = getcwd(new_path, PATH_MAX + 1);
	if (status == NULL)
		ft_path_error();
	update_paths(pipeline, envs, old_path, new_path);
	pipeline->exit_status = ER_NON;
}
