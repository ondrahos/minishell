/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daraz <daraz@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:28:15 by daraz             #+#    #+#             */
/*   Updated: 2024/04/01 10:51:24 by daraz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "build.h"

//path error
void	ft_path_error(void)
{
	ft_putstr_fd("Process terminated with path error\n", STDERR_FILENO);
	exit(ER_PATH);
}

//malloc error
void	ft_malloc_error(void)
{
	ft_putstr_fd("Process terminated with malloc error\n", STDERR_FILENO);
	exit(ER_MAL);
}

//search environment variable
char	*ft_search_env_var(t_envs_lst **envs, char *name)
{
	t_envs_lst	*curr;

	if (envs == NULL || *envs == NULL || name == NULL)
		return (NULL);
	curr = *envs;
	while (curr)
	{
		if (ft_strncmp(curr->data->name, name,
				ft_strlen(curr->data->name) + 1) == 0)
			return (curr->data->value);
		curr = curr->next;
	}
	return (NULL);
}

void	ft_free_envs(t_envs_lst **envs)
{
	t_envs_lst	*tmp;

	while (envs && *envs)
	{
		tmp = (*envs)->next;
		ft_remove_env_var(envs, (*envs)->data->name);
		*envs = tmp;
	}
}