/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daraz <daraz@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:28:21 by daraz             #+#    #+#             */
/*   Updated: 2024/03/29 14:10:10 by daraz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "build.h"

void	ft_env(t_pipeline *pipeline, t_envs_lst **envs)
{
	t_envs_lst	*curr;

	pipeline->exit_status = ER_NON;
	if (envs == NULL)
		return ;
	curr = *envs;
	while (curr != NULL)
	{
		write(STDOUT_FILENO, curr->data->name, ft_strlen(curr->data->name));
		write(STDOUT_FILENO, "=", 1);
		write(STDOUT_FILENO, curr->data->value, ft_strlen(curr->data->value));
		write(STDOUT_FILENO, "\n", 1);
		curr = curr->next;
	}
	return ;
}

/* int main(void)
{   
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
    
    // 3 nejaky variably na test
    t_variable var1 = {"PATH", "/usr/bin", NULL};
    t_variable var2 = {"HOME", "/home/user", NULL};
    t_variable var3 = {"USER", "user", NULL};

    // udelame list nasich variablu
    t_envs_lst *env_list = malloc(sizeof(t_envs_lst));
    env_list->data = &var1;
    env_list->next = malloc(sizeof(t_envs_lst));
    env_list->next->data = &var2;
    env_list->next->next = malloc(sizeof(t_envs_lst));
    env_list->next->next->data = &var3;
    env_list->next->next->next = NULL;

    ft_env(pipeline, &env_list);

    free(env_list->next->next);
    free(env_list->next);
    free(env_list);
    free(pipeline);

    return 0;
} */