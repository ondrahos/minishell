/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daraz <daraz@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:28:21 by daraz             #+#    #+#             */
/*   Updated: 2024/04/27 11:03:19 by daraz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_pipeline *pipeline, t_variable **envs)
{
	t_variable	*curr;

	pipeline->exit_status = ER_NON;
	if (envs == NULL)
		return ;
	curr = *envs;
	while (curr != NULL)
	{
		write(STDOUT_FILENO, curr->name, ft_strlen(curr->name));
		write(STDOUT_FILENO, "=", 1);
		write(STDOUT_FILENO, curr->value, ft_strlen(curr->value));
		write(STDOUT_FILENO, "\n", 1);
		curr = curr->next;
	}
	return ;
}
