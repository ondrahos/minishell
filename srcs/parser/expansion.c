/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:02:11 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/03/27 16:20:13 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	copy_beg(char *src, char *dest, int end, int *j)
{
	int	i;

	i = 0;
	while (i != end)
	{
		dest[(*j)] = src[i];
		i++;
		(*j)++;
	}
}

void	copy_end(char *src, char *dest, int end, int *j)
{
	while (src[end])
	{
		dest[(*j)] = src[end];
		end++;
		(*j)++;
	}
	dest[(*j)] = '\0';
}

void	copy_var(char *src, char *dest, int *j)
{
	int	i;

	i = 0;
	while (src && src[i])
	{
		dest[(*j)] = src[i];
		i++;
		(*j)++;
	}
}

void	expand_var(t_token *token, t_variable **variable,
					char *var, bool free_var)
{
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
	tmp = allocate_memory(var, token->value);
	if (!tmp)
		return (perror("Malloc "));
	copy_beg(token->value, tmp, beg, &j);
	copy_var(var, tmp, &j);
	copy_end(token->value, tmp, end, &j);
	replace_value(tmp, token, free_var, var);
}

void	expansion(t_pipeline **pipeline, t_variable **variable)
{
	t_pipeline	*tmp_pipe;
	t_token		*tmp_token;
	char		*var;

	tmp_pipe = *pipeline;
	var = NULL;
	while (tmp_pipe)
	{
		tmp_token = tmp_pipe->token;
		while (tmp_token)
		{
			while (is_var(tmp_token->value))
				expand_var(tmp_token, variable, var, tmp_token->free);
			tmp_token = tmp_token->next;
		}
		tmp_pipe = tmp_pipe->next;
	}
}
