/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:39:08 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/03/21 14:14:27 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	load_pipeline(char **line, t_pipeline **pipeline)
{
	int			i;
	t_pipeline	*tmp;

	i = 0;
	*pipeline = new_pipeline();
	tmp = *pipeline;
	while (line[i])
	{
		tmp->line = splitter(line[i]);
		if (line[i + 1])
			tmp->next = new_pipeline();
		tmp = tmp->next;
		i++;
	}
}

void	init_pipeline(t_pipeline *pipeline)
{
	pipeline->line = NULL;
	pipeline->in_fd = -42;
	pipeline->out_fd = -42;
	pipeline->here_doc = NULL;
	pipeline->append = false;
	pipeline->token = NULL;
	pipeline->next = NULL;
}

t_pipeline	*new_pipeline()
{
	t_pipeline	*new;

	new = (t_pipeline *)malloc(sizeof(t_pipeline));
	if (!new)
	{
		perror("Malloc ");
		return (NULL);
	}
	init_pipeline(new);
	return(new);
}

void	tokenize_pipeline(t_pipeline **pipeline)
{
	t_pipeline	*tmp;

	tmp = *pipeline;
	while (tmp)
	{
		load_token(tmp->line, &tmp->token);
		assign_type(tmp->line, &tmp->token, tmp);
		tmp = tmp->next;
	}
}