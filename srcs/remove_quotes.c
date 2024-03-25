/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:53:53 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/03/20 14:08:47 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	has_quotes(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
			return (true);
		i++;
	}
	return (false);
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
		if (s[i] == '\'')
		{
			i++;
			while (s[i] != '\'')
			{
				i++;
				len++;
			}
		}
		else if (s[i] == '\"')
		{
			i++;
			while (s[i] != '\"')
			{
				i++;
				len++;
			}
		}
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

void	remove_quotes(t_token *token)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = allocate_quotefree(token->value);
	if (!new)
	{
		perror("Malloc ");
		return ;
	}
	while (token->value[i])
	{
		while (token->value[i] && !is_quote(token->value[i]))
		{
			new[j] = token->value[i];
			i++;
			j++;
		}
		if (token->value[i] == '\"')
		{
			i++;
			while (token->value[i] != '\"')
			{
				new[j] = token->value[i];
				j++;
				i++;
			}
		}
		else if (token->value[i] == '\'')
		{
			i++;
			while (token->value[i] != '\'')
			{
				new[j] = token->value[i];
				j++;
				i++;
			}
		}
		if (token->value[i])
			i++;
	}
	new[j] = '\0';
	if (token->free == true)
		free(token->value);
	token->value = new;
	token->free = true;
}

int	check_quotes(t_token *token)
{
	if (!token->value)
		return (0);
	if (has_quotes(token->value))
	{
		remove_quotes(token);
	}
	return (0);
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
			if(check_quotes(tmp_token) != 0)
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
