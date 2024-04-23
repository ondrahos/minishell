/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daraz <daraz@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 09:56:36 by daraz             #+#    #+#             */
/*   Updated: 2024/03/31 12:34:00 by daraz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "build.h"

static t_variable	*create_new_var(char *line)
{
	int				i;
	int				j;
	t_variable	*new;

	new = (t_variable *) malloc(sizeof(t_variable));
	if (new == NULL)
		ft_malloc_error();
	i = 0;
	while (line[i] != '=')
		i++;
	new->name = ft_substr(line, 0, i);
	if (new->name == NULL)
		ft_malloc_error();
	j = i + 1;
	while (line[j] != '\0' && line[j] != '\n')
		j++;
	new->value = ft_substr(line, i + 1, j - i);
	if (new->value == NULL)
		ft_malloc_error();
	return (new);
}

static t_envs_lst	*create_env_lst_el(char *line)
{
	t_envs_lst	*new;

	new = (t_envs_lst *) malloc(sizeof(t_envs_lst));
	if (new == NULL)
		ft_malloc_error();
	new->data = create_new_var(line);
	new->next = NULL;
	return (new);
}

static void	free_env_var(t_envs_lst	*curr)
{
	free(curr->data->name);
	free(curr->data->value);
	free(curr->data);
	free(curr);
}

//add environment variable
void	ft_add_env_var(t_envs_lst **envs, char *line)
{
	t_envs_lst	*curr;

	if (line == NULL)
		return ;
	if (*envs == NULL)
		*envs = create_env_lst_el(line);
	else
	{
		curr = *envs;
		while (curr->next)
			curr = curr->next;
		curr->next = create_env_lst_el(line);
	}
}

//remove environment variable
void	ft_remove_env_var(t_envs_lst **envs, char *name)
{
	t_envs_lst	*curr;
	t_envs_lst	*tmp;

	if (envs == NULL || *envs == NULL || name == NULL)
		return ;
	curr = *envs;
	if (ft_strncmp(curr->data->name, name, ft_strlen(name) + 1) == 0)
	{
		tmp = curr->next;
		free_env_var(curr);
		*envs = tmp;
	}
	while (curr && curr->next != NULL)
	{
		if (ft_strncmp(name, curr->next->data->name,
				ft_strlen(name) + 1) == 0)
		{
			tmp = curr->next->next;
			free_env_var(curr->next);
			curr->next = tmp;
			return ;
		}
		curr = curr->next;
	}
	return ;
}