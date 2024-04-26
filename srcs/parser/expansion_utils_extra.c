/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_extra.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:44:29 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/03/27 16:54:59 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
