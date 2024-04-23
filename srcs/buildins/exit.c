/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daraz <daraz@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:22:52 by daraz             #+#    #+#             */
/*   Updated: 2024/03/29 15:54:54 by daraz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "build.h"

static int	get_argc(t_token *token)
{
	int	size;

	size = 0;
	while (token && token->type == ARGUMENT)
	{
		size++;
		token = token->next;
	}
	return (size);
}

static bool	is_numeric(char *value)
{
	int	i;

	i = 0;
	if (value[i] == '+' || value[i] == '-')
		i++;
	if (value[i] == '\0')
		return (false);
	while (value[i] != '\0')
	{
		if (!(value[i] >= '0' && value[i] <= '9'))
			return (false);
		i++;
	}
	return (true);
}

void	ft_exit(t_pipeline *pipeline, t_envs_lst **envs, t_token *token)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (token && token->value && !is_numeric(token->value))
	{
		ft_putstr_fd(ft_search_env_var(envs, "USER"), STDERR_FILENO);
		ft_putstr_fd(": exit: ", STDERR_FILENO);
		ft_putstr_fd(token->value, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit(ER_EXIT);				// Tady pripadne nemusime odchazet jako v pripade hned pod tim.
	}
	else if (get_argc(token) > 1)
	{
		ft_putstr_fd(ft_search_env_var(envs, "USER"), STDERR_FILENO);
		ft_putstr_fd(": exit: too many arguments\n", STDERR_FILENO);
		pipeline->exit_status = ER_NON; // Nebo naopak jako pripad vys (nebo error 2)
	}
	else if (!token)
		exit(ER_NON);
	else
		exit(ft_atoi(token->value) % 256);
}

/* int main() {
    
	t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    if (pipeline == NULL) {
        return 1;
    }

    pipeline->exit_status = ER_NON;
    pipeline->line = NULL;
    pipeline->in_fd = 0;
    pipeline->out_fd = 1;
    pipeline->here_doc = false;
    pipeline->append = false;
    pipeline->token = NULL;
    pipeline->next = NULL;
	
    t_token *token = malloc(sizeof(t_token));
    token->type = ARGUMENT;
    token->value = "10";
    token->free = false;
    token->next = NULL;
    
    // Call ft_exit
    t_envs_lst *envs = NULL;
    ft_exit(pipeline, &envs, token);
    
    free(token);
	free(pipeline);
    
    return 0;
} */