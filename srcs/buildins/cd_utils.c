/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daraz <daraz@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 10:38:13 by daraz             #+#    #+#             */
/*   Updated: 2024/04/01 10:57:13 by daraz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "build.h"

void	ft_handle_invalid_path(t_pipeline *pipeline, t_envs_lst **envs,
	char *path_to_go)
{
	pipeline->exit_status = ER_MAIN;
	ft_putstr_fd(ft_search_env_var(envs, "USER"), STDERR_FILENO);
	ft_putstr_fd(": cd: ", STDERR_FILENO);
	ft_putstr_fd(path_to_go, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
}

bool	ft_handle_empty_path(t_pipeline *pipeline, t_envs_lst **envs)
{
	char	*home_path;

	home_path = ft_search_env_var(envs, "HOME");
	if (home_path == NULL)
	{
		pipeline->exit_status = ER_MAIN;
		ft_putstr_fd(home_path, STDERR_FILENO);
		ft_putstr_fd(": cd: HOME not set", STDERR_FILENO);
		return (false);
	}
	else
	{
		if (chdir(home_path) == -1)
		{
			ft_handle_invalid_path(pipeline, envs, home_path);
			return (false);
		}
		return (true);
	}
}