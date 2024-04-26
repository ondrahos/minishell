/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:53:53 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/03/27 17:22:00 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	skip_quotes(char *s, int *i, int *len)
{
	if (s[(*i)] == '\'')
	{
		(*i)++;
		while (s[(*i)] != '\'')
		{
			(*i)++;
			(*len)++;
		}
	}
	else if (s[(*i)] == '\"')
	{
		(*i)++;
		while (s[(*i)] != '\"')
		{
			(*i)++;
			(*len)++;
		}
	}
}

char	*allocate_quotefree(char *s)
{
	int		i;
	int		len;
	char	*new;

	i = 0;
	len = 0;
	while (s[i])
	{
		while (s[i] && !is_quote(s[i]))
		{
			len++;
			i++;
		}
		skip_quotes(s, &i, &len);
		if (s[i])
			i++;
	}
	new = (char *)malloc((len + 1) * sizeof(char));
	if (!new)
	{
		perror("Malloc ");
		return (NULL);
	}
	return (new);
}

void	process_quotes(t_token *token, int *i, int *j, char *new)
{
	if (token->value[(*i)] == '\"')
	{
		(*i)++;
		while (token->value[(*i)] != '\"')
		{
			new[(*j)] = token->value[(*i)];
			(*j)++;
			(*i)++;
		}
	}
	else if (token->value[(*i)] == '\'')
	{
		(*i)++;
		while (token->value[(*i)] != '\'')
		{
			new[(*j)] = token->value[(*i)];
			(*j)++;
			(*i)++;
		}
	}
}

void	remove_quotes(t_token *token)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = allocate_quotefree(token->value);
	if (!new)
		return (perror("Malloc "));
	while (token->value[i])
	{
		while (token->value[i] && !is_quote(token->value[i]))
		{
			new[j] = token->value[i];
			i++;
			j++;
		}
		process_quotes(token, &i, &j, new);
		if (token->value[i])
			i++;
	}
	new[j] = '\0';
	replace_value(new, token, token->free, NULL);
}

int	handle_quotes(t_pipeline **pipeline)
{
	t_pipeline	*tmp_pipe;
	t_token		*tmp_token;

	tmp_pipe = *pipeline;
	while (tmp_pipe)
	{
		tmp_token = tmp_pipe->token;
		while (tmp_token)
		{
			if (check_quotes(tmp_token) != 0)
			{
				ft_putendl_fd("Syntax error: Unclosed quotes", STDERR_FILENO);
				return (1);
			}
			tmp_token = tmp_token->next;
		}
		tmp_pipe = tmp_pipe->next;
	}
	return (0);
}
