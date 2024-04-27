/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daraz <daraz@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 09:56:36 by daraz             #+#    #+#             */
/*   Updated: 2024/04/27 11:03:39 by daraz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_variable	*create_new_var(char *line)
{
	int			i;
	int			j;
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
	new->next = NULL;
	return (new);
}

static void	free_env_var(t_variable	*curr)
{
	free(curr->name);
	free(curr->value);
	free(curr);
}

void	ft_add_env_var(t_variable **envs, char *line)
{
	t_variable	*curr;

	if (line == NULL)
		return ;
	if (*envs == NULL)
		*envs = create_new_var(line);
	else
	{
		curr = *envs;
		while (curr && curr->next)
			curr = curr->next;
		curr->next = create_new_var(line);
	}
}

void	ft_remove_env_var(t_variable **envs, char *name)
{
	t_variable	*curr;
	t_variable	*tmp;

	if (envs == NULL || *envs == NULL || name == NULL)
		return ;
	curr = *envs;
	if (ft_strncmp(curr->name, name, ft_strlen(name) + 1) == 0)
	{
		tmp = curr->next;
		free_env_var(curr);
		*envs = tmp;
	}
	while (curr && curr->next != NULL)
	{
		if (ft_strncmp(name, curr->next->name,
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
