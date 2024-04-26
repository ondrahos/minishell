/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:22:35 by daraz             #+#    #+#             */
/*   Updated: 2024/04/23 20:23:04 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**sort(char **tab, int size)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strncmp(tab[j], tab[j + 1], ft_strlen(tab[j]) + 1) > 0)
			{
				temp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
	return (tab);
}

static int	get_num_of_keys(t_variable **envs)
{
	int			size;
	t_variable	*curr;

	size = 0;
	curr = *envs;
	while (curr)
	{
		size++;
		curr = curr->next;
	}
	return (size);
}

void	ft_free_sorted_keys(char **keys, int size)
{
	int	i;

	if (keys == NULL)
		return ;
	i = -1;
	while (++i < size)
		free(keys[i]);
	free(keys);
}

char	**ft_get_sorted_keys(t_variable **envs)
{
	char		**keys;
	int			size;
	int			i;
	t_variable	*curr;

	if (envs == NULL)
		return (NULL);
	size = get_num_of_keys(envs);
	keys = (char **) malloc(sizeof(char *) * (size + 1));
	if (keys == NULL)
		ft_malloc_error();
	i = -1;
	curr = *envs;
	while (++i > -1 && curr)
	{
		keys[i] = ft_strjoin(curr->name, "");
		if (keys[i] == NULL)
			ft_malloc_error();
		curr = curr->next;
	}
	keys[i] = NULL;
	return (sort(keys, size));
}

void	ft_handle_export_error(t_pipeline *pipeline, t_variable **envs,
	char *arg)
{
	pipeline->exit_status = ER_MAIN;
	ft_putstr_fd(ft_search_env_var(envs, "USER"), STDERR_FILENO);
	ft_putstr_fd(": export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}
