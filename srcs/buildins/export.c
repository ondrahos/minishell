/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daraz <daraz@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:43:37 by daraz             #+#    #+#             */
/*   Updated: 2024/04/23 13:01:43 by daraz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "build.h"

static bool	check_eq_sign(t_token *token)
{
	int	i;

	i = 0;
	while (token->value && token->value[i] != '\0')
	{
		if (token->value[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

static bool	check_key_validity(t_token *token)
{
	int	i;

	i = 0;
	while (token->value && token->value[i] != '\0' && token->value[i] != '=')
		i++;
	return (i > 0);
}

static void	handle_existing_key(t_envs_lst **envs, t_token *token)
{
	int		i;
	char	*key;

	i = 0;
	while (token->value && token->value[i] != '=')
		i++;
	key = ft_substr(token->value, 0, i);
	if (key == NULL)
		ft_malloc_error();
	if (ft_search_env_var(envs, key) != NULL)
		ft_remove_env_var(envs, key);
	free(key);
}

static void	handle_empty_export(t_envs_lst **envs)
{
	t_envs_lst	*curr;
	char		**keys;
	int			i;

	if (envs == NULL || *envs == NULL)
		return ;
	curr = *envs;
	i = -1;
	keys = ft_get_sorted_keys(envs);
	while (keys && keys[++i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(keys[i], STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putstr_fd(ft_search_env_var(envs, keys[i]), STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		curr = curr->next;
	}
	if (keys)
		ft_free_sorted_keys(keys, i);
}

void	ft_export(t_pipeline *pipeline, t_envs_lst **envs, t_token *token)
{
	if (token == NULL || token->type != ARGUMENT)
		handle_empty_export(envs);
	else
	{		
		while (token && token->value && token->type == ARGUMENT)
		{
			if (!ft_check_env_syntax(token->value) || !check_key_validity(token))
				ft_handle_export_error(pipeline, envs, token);
			else if (!check_eq_sign(token))
				pipeline->exit_status = ER_NON;
			else
			{
				handle_existing_key(envs, token);
				ft_add_env_var(envs, token->value);
				pipeline->exit_status = ER_NON;
			}
			token = token->next;
		}
	}
}



/* void print_envs(t_envs_lst *envs) {
    printf("Environment Variables:\n");
    while (envs != NULL) {
        printf("%s=%s\n", envs->data->name, envs->data->value);
        envs = envs->next;
    }
    printf("\n");
}

int main() {

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
    // Create a linked list of environment variables
    t_envs_lst *envs = NULL; // Initialize to empty list
    // Add some initial environment variables for testing
    ft_add_env_var(&envs, "VARIABLE_1=VALUE_1");
    ft_add_env_var(&envs, "VARIABLE_2=VALUE_2");

    // Print the initial contents of the environment variables list
    printf("Before exporting:\n");
    print_envs(envs);

    // Create some tokens representing variables to export
    t_token *token1 = malloc(sizeof(t_token));
    token1->type = ARGUMENT;
    token1->value = "VARIABLE_3=VALUE_3";
    token1->free = false;

    t_token *token2 = malloc(sizeof(t_token));
    token2->type = ARGUMENT;
    token2->value = "VARIABLE_4"; // Assuming this doesn't exist
    token2->free = false;

    // Link tokens together
    token1->next = token2;
    token2->next = NULL;

    // Call ft_export function
    ft_export(pipeline, &envs, token1); // Pass NULL for pipeline since it's not used

    // Print the contents of the environment variables list after exporting
    printf("After exporting:\n");
    print_envs(envs);

    // Free memory
    //ft_free_envs(&envs);
    //free(pipeline);
    //free(token1);
    //free(token2);

    return 0;
} */