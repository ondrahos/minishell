/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:12:31 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/03/27 16:20:25 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*allocate_memory(char *var, char *value)
{
	char	*tmp;

	if (var)
		tmp = (char *)malloc(ft_strlen(value)
				- get_name_len(value) + ft_strlen(var) + 1);
	else
		tmp = (char *)malloc(ft_strlen(value)
				- get_name_len(value) + 1);
	return (tmp);
}

char	*ft_getenv(char *name, t_variable **variable)
{
	char		*env;
	t_variable	*tmp;

	tmp = *variable;
	while (tmp)
	{
		if (ft_strncmp(name, tmp->name, ft_strlen(name) + 1) == 0)
		{
			env = (char *)malloc((ft_strlen(tmp->value) + 1) * sizeof(char));
			if (!env)
			{
				perror("Malloc ");
				return (NULL);
			}
			ft_strlcpy(env, tmp->value, ft_strlen(tmp->value) + 1);
			return (env);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	get_size(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !is_whitespace(str[i]))
		i++;
	return (i);
}

char	*get_var(char *value, t_variable **variable)
{
	int		i;
	int		j;
	char	*var_name;
	char	*ret;

	i = 0;
	j = 0;
	while (value[i] != '$')
		i++;
	i++;
	if (value[i] == '?')
		return (ft_getenv("?", variable));
	var_name = (char *)malloc(get_size(value + i) + 1);
	if (!var_name)
	{
		perror("Malloc ");
		return (NULL);
	}
	while (value[i] && is_alphanum(value[i]))
		var_name[j++] = value[i++];
	var_name[j] = '\0';
	ret = ft_getenv(var_name, variable);
	free(var_name);
	var_name = NULL;
	return (ret);
}

int	get_name_len(char *s)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i] != '$')
		i++;
	i++;
	while (s[i] && is_alphanum(s[i]))
	{
		len++;
		i++;
	}
	return (len);
}
