/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_variables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:03:25 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/03/20 16:43:15 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_var_value(char *envp)
{
	char	*value;
	int		i;

	i = 0;
	while (*envp != '=')
		envp++;
	envp++;
	value = (char *)malloc(ft_strlen(envp) + 1);
	if (!value)
	{
		perror("Malloc ");
		return (NULL);
	}
	while (envp[i])
	{
		value[i] = envp[i];
		i++;
	}
	value[i] = '\0';
	return (value);
}

char	*get_var_name(char *envp)
{
	int		i;
	int		j;
	char	*name;

	i = 0;
	j = 0;
	while (envp[i] != '=')
		i++;
	name = (char *)malloc((i + 1) * sizeof(char));
	if (!name)
	{
		perror("Malloc ");
		return (NULL);
	}
	while (j < i)
	{
		name[j] = envp[j];
		j++;
	}
	name[j] = '\0';
	return (name);
}

void	init_variable(t_variable *variable)
{
	variable->name = NULL;
	variable->value = NULL;
	variable->next = NULL;
}

t_variable	*new_variable()
{
	t_variable	*new;

	new = (t_variable *)malloc(sizeof(t_variable));
	if (!new)
	{
		perror("Malloc ");
		return (NULL);
	}
	init_variable(new);
	return(new);
}

t_variable	*add_exitstatus()
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

