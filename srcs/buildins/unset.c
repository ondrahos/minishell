/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daraz <daraz@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:11:37 by daraz             #+#    #+#             */
/*   Updated: 2024/03/29 14:41:56 by daraz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "build.h"

void	ft_unset(t_pipeline *pipeline, t_envs_lst **envs, t_token *token)
{
	while (token && token->type == ARGUMENT)
	{
		if (!ft_check_env_syntax(token->value))
		{
			pipeline->exit_status = ER_MAIN;
			ft_putstr_fd(ft_search_env_var(envs, "USER"), STDERR_FILENO);
			ft_putstr_fd(": unset: `", STDERR_FILENO);
			ft_putstr_fd(token->value, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		}
		else
		{
			ft_remove_env_var(envs, token->value);
			pipeline->exit_status = ER_NON;
		}
		token = token->next;
	}
	pipeline->exit_status = ER_NON;
}