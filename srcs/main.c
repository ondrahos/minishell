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

void	print_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		printf("%s ", arr[i]);
		if (arr[i + 1])
			printf(", ");
		i++;
	}
	printf("\n-------------------------------------------------\n");
}

void	print_tokens(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	printf("Tokens: \n\n");
	while (tmp)
	{
		printf("%s (Type: %i)", tmp->value, tmp->type);
		if (tmp->next)
			printf("\n");
		tmp = tmp->next;
	}
	printf("\n--------------------------------------------------------------------------------------------------\n");
}

void	print_pipeline(t_pipeline **pipeline)
{
	t_pipeline	*tmp;

	if (!pipeline || !(*pipeline))
		return ;
	tmp = *pipeline;
	printf("--------------------------------------------------------------------------------------------------\n");
	while (tmp)
	{
		printf("Here_doc: %d\n", tmp->here_doc);
		printf("Append: %d\n\n", tmp->append);
		printf("Infile: %i\n", tmp->in_fd);
		printf("Outfile: %i\n\n", tmp->out_fd);
		print_tokens(&tmp->token);
		tmp = tmp->next;
	}
}

void	print_variable(t_variable **variable)
{
	t_variable	*tmp;

	tmp = *variable;
	while (tmp)
	{
		printf("NAME: %s\n", tmp->name);
		printf("VALUE: %s\n\n", tmp->value);
		tmp = tmp->next;
	}
}

void	executer(t_pipeline **pipeline, t_variable **variable, char **envp)
{
	t_data	data;
	int		i;
	int		original_stdin = dup(STDIN_FILENO);
	int		original_stdout = dup(STDOUT_FILENO);

	i = 0;
	data.pipeline_count = count_pipelines(pipeline) - 1;
	data.pipes = allocate_pipes(data.pipeline_count);
	data.pids = allocate_pids(data.pipeline_count);
	data.envp = envp;
	if (data.pipeline_count == 0)
	{
		execute_one(pipeline, data, variable);
		return ;
	}
	while (i < data.pipeline_count)
	{
		if (pipe(data.pipes[i]) < 0)
			return (perror("Pipe "));
		i++;
	}
	i = 0;
	while (i < data.pipeline_count + 1)
	{
		data.pids[i] = fork();
		if (data.pids[i] < 0)
			return (perror("Fork "));
		if (data.pids[i] == 0)
		{
			dup_io(pipeline, i);
			if (i != data.pipeline_count)
				dup2(data.pipes[i][1], STDOUT_FILENO);
			if (i != 0)
				dup2(data.pipes[i - 1][0], STDIN_FILENO);
			close_all_pipes(data.pipes, data.pipeline_count);
			execute(pipeline, data, i, variable);
			break ;
		}
		i++;
	}
	close_all_pipes(data.pipes, data.pipeline_count);
	i = 0;
	while (i < data.pipeline_count + 1)
	{
		wait(NULL);
		i++;
	}
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
}

void	parser(char *buffer, t_pipeline **pipeline, t_variable **variable)
{
	char		**line;

	line = ft_split(buffer, '|');
	if (load_pipeline(line, pipeline) != 0)
		return (free_array(line));
	tokenize_pipeline(pipeline);
	if (check_syntax(pipeline) != 0 || check_pipes(buffer) != 0)
		return (free_array(line));
	//print_variable(variable);
	expansion(pipeline, variable);
	if (handle_quotes(pipeline) != 0 || handle_files(pipeline) != 0)
		return (free_array(line));
	print_pipeline(pipeline);
	free_array(line);
}

int	main(int ac, char **av, char **envp)
{
	char		*buffer;
	t_pipeline	*pipeline;
	t_variable	*variable;

	pipeline = NULL;
	variable = NULL;
	while (1)
	{
		buffer = readline("$ minishell> ");
		if (ft_strncmp(buffer, "", 2) == 0)
		{
			free(buffer);
			continue ;
		}
		if (ft_strncmp(buffer, "exit", 5) == 0 || buffer == NULL)
		{
			free(buffer);
			buffer = NULL;
			break ;
		}
		if (variable == NULL)
			load_variable(&variable, envp);
		add_history(buffer);
		parser(buffer, &pipeline, &variable);
		executer(&pipeline, &variable, envp);
		free_pipeline(&pipeline);
		free(buffer);
		buffer = NULL;
	}
	free_variable(&variable);
	if (av)
		return (ac);
	return (0);
}
