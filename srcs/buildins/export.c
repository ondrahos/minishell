/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:43:37 by daraz             #+#    #+#             */
/*   Updated: 2024/04/23 20:34:13 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	check_eq_sign(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

static bool	check_key_validity(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0' && arg[i] != '=')
		i++;
	return (i > 0);
}

static void	handle_existing_key(t_variable **envs, char *arg)
{
	int		i;
	char	*key;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	key = ft_substr(arg, 0, i);
	if (key == NULL)
		ft_malloc_error();
	if (ft_search_env_var(envs, key) != NULL)
		ft_remove_env_var(envs, key);
	free(key);
}

static void	handle_empty_export(t_variable **envs)
{
	t_variable	*curr;
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

void	ft_export(t_pipeline *pipeline, t_variable **envs, char **cmd)
{
	int	i;

	i = 1;
	if (cmd[1] == NULL)
		handle_empty_export(envs);
	else
	{
		while (cmd[i])
		{
			if (!ft_check_env_syntax(cmd[i]) || !check_key_validity(cmd[i]))
				ft_handle_export_error(pipeline, envs, cmd[i]);
			else if (!check_eq_sign(cmd[i]))
				pipeline->exit_status = ER_NON;
			else
			{
				handle_existing_key(envs, cmd[i]);
				ft_add_env_var(envs, cmd[i]);
				pipeline->exit_status = ER_NON;
			}
			i++;
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
