/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:36:53 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/03/21 16:02:33 by ohosnedl         ###   ########.fr       */
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
		printf("Here_doc: %s\n", tmp->here_doc);
		printf("Append: %d\n\n", tmp->append);
		printf("Infile: %i\n", tmp->in_fd);
		printf("Outfile: %i\n\n", tmp->out_fd);
		print_tokens(&tmp->token);
		tmp = tmp->next;
	}
}

/* void	print_variable(t_variable **variable)
{
	t_variable	*tmp;

	tmp = *variable;
	while (tmp)
	{
		printf("NAME: %s\n", tmp->name);
		printf("VALUE: %s\n\n", tmp->value);
		tmp = tmp->next;
	}
} */


void	parser(char *buffer, t_pipeline **pipeline, char **envp, t_variable **variable)
{
	char		**line;

	line = ft_split(buffer, '|');
	load_pipeline(line, pipeline);
	tokenize_pipeline(pipeline);
	load_variable(variable, envp);
	/* print_variable(variable); */
	expansion(pipeline, variable);
	if (handle_quotes(pipeline) != 0 /* || handle_files(pipeline) != 0 */)
	{
		free_array(line);
		return ;
	}
	print_pipeline(pipeline);
	free_array(line);
}

int	main(int ac, char **av, char **envp)
{
	char		*buffer;
	t_pipeline	*pipeline;
	t_variable	*variable;

	pipeline = NULL;
	while(1)
	{
		buffer = readline("minishell$ ");
		if (ft_strncmp(buffer, "", 2) == 0)
		{
			free(buffer);
			continue ;
		}
		if (ft_strncmp(buffer, "exit", 5) == 0)
		{
			free(buffer);
			buffer = NULL;
			break ;
		}
		parser(buffer, &pipeline, envp, &variable);
		free_pipeline(&pipeline);
		free(buffer);
		buffer = NULL;
	}
	free_variable(&variable);
	if (av)
		return (ac);
	return (0);
}
