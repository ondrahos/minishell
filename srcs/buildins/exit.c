/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:22:52 by daraz             #+#    #+#             */
/*   Updated: 2024/04/26 20:46:53 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_argc(char **cmd)
{
	int	size;
	int	i;

	size = 0;
	i = 1;
	while (cmd[i])
	{
		size++;
		i++;
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

void	ft_exit(t_pipeline *pipeline, t_variable **envs, char **cmd, int pipe_count)
{
	if (pipe_count == 0)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (get_argc(cmd) > 1)
	{
		ft_putstr_fd(ft_search_env_var(envs, "USER"), STDERR_FILENO);
		ft_putstr_fd(": exit: too many arguments\n", STDERR_FILENO);
		pipeline->exit_status = ER_NON; // Nebo naopak jako pripad vys (nebo error 2)
	}
	else if (cmd[1] && !is_numeric(cmd[1]))
	{
		ft_putstr_fd(ft_search_env_var(envs, "USER"), STDERR_FILENO);
		ft_putstr_fd(": exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit(ER_EXIT);				// Tady pripadne nemusime odchazet jako v pripade hned pod tim.
	}
	else if (!cmd[1])
		exit(ER_NON);
	else
		exit(ft_atoi(cmd[1]) % 256);
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
