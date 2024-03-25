/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:02:11 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/03/21 13:36:14 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_alphanum(char c)
{
	if ((c <= 'Z' && c >= 'A') || (c <= 'z' && c >= 'a')
		|| (c >= '0' && c <= '9') || c == '_')
		return (true);
	return (false);
}

bool	is_var(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[0] != '\'' && value[ft_strlen(value) - 1] != '\'' && value[i] == '$' )
			return (true);
		i++;
	}
	return (false);
}

bool	is_whitespace(char c)
{
	return (c == ' ' || (c >=  9 && c <= 13));
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

void	expand_var(t_token *token, t_variable **variable)
{
	char	*var;
	int		beg;
	int		end;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	var = get_var(token->value, variable);
	while (token->value[i] != '$')
		i++;
	beg = i++;
	if (token->value[i] == '?')
		i++;
	else
		while (token->value[i] && is_alphanum(token->value[i]))
			i++;
	end = i;
	if (var)
		tmp = (char *)malloc(end + beg + ft_strlen(var) + 1);
	else
		tmp = (char *)malloc(end + beg + 1);
	if (!tmp)
	{
		perror("Malloc ");
		return ;
	}
	i = 0;
	while (i != beg)
		tmp[j++] = token->value[i++];
	i = 0;
	while (var && var[i])
		tmp[j++] = var[i++];
	while (token->value[end])
		tmp[j++] = token->value[end++];
	tmp[j] = '\0';
	free(var);
	var = NULL;
	token->value = tmp;
	token->free = true;
}

void	expansion(t_pipeline **pipeline, t_variable **variable)
{
	t_pipeline	*tmp_pipe;
	t_token		*tmp_token;


	tmp_pipe = *pipeline;
	while (tmp_pipe)
	{
		tmp_token = tmp_pipe->token;
		while (tmp_token)
		{
			if (is_var(tmp_token->value))
				expand_var(tmp_token, variable);
			tmp_token = tmp_token->next;
		}
		tmp_pipe = tmp_pipe->next;
	}
}
