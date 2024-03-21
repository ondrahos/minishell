/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:12:31 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/03/21 13:19:14 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
