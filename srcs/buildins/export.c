/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daraz <daraz@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:43:37 by daraz             #+#    #+#             */
/*   Updated: 2024/04/27 11:02:51 by daraz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	check_eq_sign(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

static bool	check_key_validity(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0' && arg[i] != '=')
		i++;
	return (i > 0);
}

static void	handle_existing_key(t_variable **envs, char *arg)
{
	int		i;
	char	*key;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	key = ft_substr(arg, 0, i);
	if (key == NULL)
		ft_malloc_error();
	if (ft_search_env_var(envs, key) != NULL)
		ft_remove_env_var(envs, key);
	free(key);
}

static void	handle_empty_export(t_variable **envs)
{
	t_variable	*curr;
	char		**keys;
	int			i;

	if (envs == NULL || *envs == NULL)
		return ;
	curr = *envs;
	i = -1;
	keys = ft_get_sorted_keys(envs);
	while (keys && keys[++i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(keys[i], STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putstr_fd(ft_search_env_var(envs, keys[i]), STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		curr = curr->next;
	}
	if (keys)
		ft_free_sorted_keys(keys, i);
}

void	ft_export(t_pipeline *pipeline, t_variable **envs, char **cmd)
{
	int	i;

	i = 1;
	if (cmd[1] == NULL)
		handle_empty_export(envs);
	else
	{
		while (cmd[i])
		{
			if (!ft_check_env_syntax(cmd[i]) || !check_key_validity(cmd[i]))
				ft_handle_export_error(pipeline, envs, cmd[i]);
			else if (!check_eq_sign(cmd[i]))
				pipeline->exit_status = ER_NON;
			else
			{
				handle_existing_key(envs, cmd[i]);
				ft_add_env_var(envs, cmd[i]);
				pipeline->exit_status = ER_NON;
			}
			i++;
		}
	}
}
