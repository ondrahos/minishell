/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:17:18 by daraz             #+#    #+#             */
/*   Updated: 2024/04/23 20:22:31 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(char **cmd, t_pipeline *pipeline)
{
	bool	is_newline;
	int		i;

	is_newline = false;
	i = 1;
	while (cmd[i] && ft_strncmp(cmd[i], "-n", ft_strlen("-n") + 1) == 0)
		i++;
	while (cmd[i])
	{
		write(STDOUT_FILENO, cmd[i], ft_strlen(cmd[i]));
		if (cmd[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (is_newline)
		write(STDOUT_FILENO, "\n", 1);
	pipeline->exit_status = ER_NON;
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

    // Tvorba nekolika tokenu
    t_token *token1 = malloc(sizeof(t_token));
    token1->type = 3;
    token1->value = "-n";
    token1->free = false;

    t_token *token2 = malloc(sizeof(t_token));
    token2->type = ARGUMENT;
    token2->value = "Hello";
    token2->free = false;

    t_token *token3 = malloc(sizeof(t_token));
    token3->type = ARGUMENT;
    token3->value = "World";
    token3->free = false;


    // Linkujeme tokeny dohromady
    token1->next = token2;
    token2->next = token3;
    token3->next = NULL;

    // Call ft_echo
    ft_echo(pipeline, token1);

    free(token1);
    free(token2);
    free(token3);
    free(pipeline);

    return 0;
} */
