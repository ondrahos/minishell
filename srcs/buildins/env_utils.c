/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daraz <daraz@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:28:15 by daraz             #+#    #+#             */
/*   Updated: 2024/04/27 11:03:31 by daraz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_path_error(void)
{
	ft_putstr_fd("Process terminated with path error\n", STDERR_FILENO);
	exit(ER_PATH);
}

void	ft_malloc_error(void)
{
	ft_putstr_fd("Process terminated with malloc error\n", STDERR_FILENO);
	exit(ER_MAL);
}

char	*ft_search_env_var(t_variable **envs, char *name)
{
	t_variable	*curr;

	if (envs == NULL || *envs == NULL || name == NULL)
		return (NULL);
	curr = *envs;
	while (curr)
	{
		if (curr->name && ft_strncmp(curr->name, name,
				ft_strlen(curr->name) + 1) == 0)
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}
