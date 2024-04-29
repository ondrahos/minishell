/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:11:37 by daraz             #+#    #+#             */
/*   Updated: 2024/04/29 20:36:42 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_unset(t_pipeline *pipeline, t_variable **envs, char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (!ft_check_env_syntax(cmd[i]))
		{
			pipeline->exit_status = ER_MAIN;
			ft_putstr_fd(ft_search_env_var(envs, "USER"), STDERR_FILENO);
			ft_putstr_fd(": unset: `", STDERR_FILENO);
			ft_putstr_fd(cmd[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		}
		else
		{
			ft_remove_env_var(envs, cmd[i]);
			pipeline->exit_status = ER_NON;
		}
		i++;
	}
}
