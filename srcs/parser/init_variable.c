/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_variable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:03:25 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/03/27 16:45:38 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_variable(t_variable *variable)
{
	variable->name = NULL;
	variable->value = NULL;
	variable->next = NULL;
}

t_variable	*new_variable(void)
{
	t_variable	*new;

	new = (t_variable *)malloc(sizeof(t_variable));
	if (!new)
	{
		perror("Malloc ");
		return (NULL);
	}
	init_variable(new);
	return (new);
}

t_variable	*add_exitstatus(void)
{
	t_variable	*new;

	new = new_variable();
	new->name = ft_strdup("?");
	new->value = ft_strdup("0");
	return (new);
}

void	load_variable(t_variable **variable, char **envp)
{
	int			i;
	t_variable	*tmp;

	i = 0;
	*variable = add_exitstatus();
	tmp = *variable;
	tmp->next = new_variable();
	tmp = tmp->next;
	while (envp[i])
	{
		tmp->name = get_var_name(envp[i]);
		tmp->value = get_var_value(envp[i]);
		if (envp[i + 1])
			tmp->next = new_variable();
		tmp = tmp->next;
		i++;
	}
}
