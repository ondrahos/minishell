/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daraz <daraz@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:22:52 by daraz             #+#    #+#             */
/*   Updated: 2024/04/27 11:05:23 by daraz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_argc(char **cmd)
{
	int	size;
	int	i;

	size = 0;
	i = 1;
	while (cmd[i])
	{
		size++;
		i++;
	}
	return (size);
}

static bool	is_numeric(char *value)
{
	int	i;

	i = 0;
	if (value[i] == '+' || value[i] == '-')
		i++;
	if (value[i] == '\0')
		return (false);
	while (value[i] != '\0')
	{
		if (!(value[i] >= '0' && value[i] <= '9'))
			return (false);
		i++;
	}
	return (true);
}

void	ft_exit(t_pipeline *pipeline, t_variable **envs,
	char **cmd, int pipe_count)
{
	if (pipe_count == 0)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (get_argc(cmd) > 1)
	{
		ft_putstr_fd(ft_search_env_var(envs, "USER"), STDERR_FILENO);
		ft_putstr_fd(": exit: too many arguments\n", STDERR_FILENO);
		pipeline->exit_status = ER_NON;
	}
	else if (cmd[1] && !is_numeric(cmd[1]))
	{
		ft_putstr_fd(ft_search_env_var(envs, "USER"), STDERR_FILENO);
		ft_putstr_fd(": exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit(ER_EXIT);
	}
	else if (!cmd[1])
		exit(ER_NON);
	else
		exit(ft_atoi(cmd[1]) % 256);
}
