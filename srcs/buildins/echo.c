/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daraz <daraz@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:17:18 by daraz             #+#    #+#             */
/*   Updated: 2024/04/27 11:03:45 by daraz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(char **cmd, t_pipeline *pipeline)
{
	bool	is_newline;
	int		i;

	is_newline = false;
	i = 1;
	while (cmd[i] && ft_strncmp(cmd[i], "-n", ft_strlen("-n") + 1) == 0)
		i++;
	while (cmd[i])
	{
		write(STDOUT_FILENO, cmd[i], ft_strlen(cmd[i]));
		if (cmd[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (is_newline)
		write(STDOUT_FILENO, "\n", 1);
	pipeline->exit_status = ER_NON;
}
