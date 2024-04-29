/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:36:53 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/03/26 16:24:54 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parser(char *buffer, t_pipeline **pipeline, t_variable **variable)
{
	char		**line;

	line = pipe_split(buffer, '|');
	if (load_pipeline(line, pipeline) != 0)
		return (free_array(line), 1);
	tokenize_pipeline(pipeline);
	if (!(*pipeline)->token->value)
		return (free_array(line), 1);
	if (check_syntax(pipeline) != 0 || check_pipes(buffer) != 0)
		return (free_array(line), 1);
	expansion(pipeline, variable);
	if (handle_quotes(pipeline) != 0)
		return (free_array(line), 1);
	free_array(line);
	return (0);
}

int	minishell(t_pipeline **pipeline, t_variable **variable,
				char **envp, char *buffer)
{
	int	ret;

	ret = 0;
	add_history(buffer);
	if (parser(buffer, pipeline, variable) == 1)
		ret = 1;
	if (ret == 0)
		executer(pipeline, variable, envp);
	free_pipeline(pipeline);
	free(buffer);
	buffer = NULL;
	return (ret);
}

int	handle_input(char *buffer)
{
	if (buffer == NULL)
	{
		write(1, "exit\n", 6);
		return (1);
	}
	if (ft_strncmp(buffer, "", 2) == 0)
	{
		free(buffer);
		return (2);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	char		*buffer;
	t_pipeline	*pipeline;
	t_variable	*variable;

	pipeline = NULL;
	variable = NULL;
	(void)ac;
	(void)av;
	while (1)
	{
		ft_tty_mask();
		ft_start_signals();
		buffer = readline("$ minishell> ");
		if (handle_input(buffer) == 2)
			continue ;
		if (buffer == NULL)
			break ;
		if (variable == NULL)
			load_variable(&variable, envp);
		if (minishell(&pipeline, &variable, envp, buffer) == 1)
			continue ;
	}
	free_variable(&variable);
	return (0);
}
