/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:58:49 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/04/26 20:38:18 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_status(int status, t_variable **variable)
{
	t_variable	*tmp;
	char		*new_value;

	tmp = *variable;
	while (ft_strncmp(tmp->name, "?", 1) != 0)
		tmp = tmp->next;
	new_value = ft_itoa(status);
	free(tmp->value);
	tmp->value = new_value;
}

void	check_pipeline_status(t_data *data, t_pipeline **pipeline)
{
	t_pipeline	*tmp;

	tmp = *pipeline;
	while (tmp->next)
		tmp = tmp->next;
	if (tmp->exit_status != -42)
		data->status = tmp->exit_status;
}
