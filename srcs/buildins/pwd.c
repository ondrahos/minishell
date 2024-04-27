/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daraz <daraz@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:43:28 by daraz             #+#    #+#             */
/*   Updated: 2024/04/27 11:02:39 by daraz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(t_pipeline *pipeline)
{
	char	pwd[PATH_MAX + 1];
	char	*status;

	pipeline->exit_status = ER_NON;
	status = getcwd(pwd, PATH_MAX + 1);
	if (status == NULL)
		return ;
	write(STDOUT_FILENO, pwd, ft_strlen(pwd));
	write(STDOUT_FILENO, "\n", 1);
}
