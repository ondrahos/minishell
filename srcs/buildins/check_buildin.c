/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_buildin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:09:38 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/05/09 18:10:30 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_buildin(char **cmd, t_variable **variable,
	t_pipeline *pipeline, int pipe_count)
{
	if (!cmd[0])
		return (false);
	if (ft_strncmp(cmd[0], "echo", 4) == 0 && cmd[1]
		&& ft_strncmp(cmd[1], "-n", 2) == 0)
		return (ft_echo(cmd, pipeline), true);
	else if (ft_strncmp(cmd[0], "cd", 2) == 0)
		return (ft_cd(pipeline, variable, cmd), true);
	else if (ft_strncmp(cmd[0], "pwd", 3) == 0)
		return (ft_pwd(pipeline), true);
	else if (ft_strncmp(cmd[0], "export", 6) == 0)
		return (ft_export(pipeline, variable, cmd), true);
	else if (ft_strncmp(cmd[0], "unset", 5) == 0)
		return (ft_unset(pipeline, variable, cmd), true);
	else if (ft_strncmp(cmd[0], "env", 3) == 0)
		return (ft_env(pipeline, variable), true);
	else if (ft_strncmp(cmd[0], "exit", 4) == 0)
		return (ft_exit(pipeline, variable, cmd, pipe_count), true);
	return (false);
}
