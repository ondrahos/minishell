/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daraz <daraz@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 10:38:02 by daraz             #+#    #+#             */
/*   Updated: 2024/04/01 11:11:55 by daraz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "build.h"

static void	update_old_path(t_pipeline *pipeline, t_envs_lst **envs, char *old_path)
{
	t_token		new_token;

	ft_remove_env_var(envs, "OLDPWD");
	new_token.value = ft_strjoin("OLDPWD=", old_path);
	if (new_token.value == NULL)
		ft_malloc_error();
	new_token.next = NULL;
	new_token.prev = NULL;
	new_token.type = ARGUMENT;
	ft_export(pipeline, envs, &new_token);
	free(new_token.value);
}

static void	update_new_path(t_pipeline *pipeline, t_envs_lst **envs, char *new_path)
{
	t_token		new_token;

	ft_remove_env_var(envs, "PWD");
	new_token.value = ft_strjoin("PWD=", new_path);
	if (new_token.value == NULL)
		ft_malloc_error();
	new_token.next = NULL;
	new_token.prev = NULL;
	new_token.type = ARGUMENT;
	new_token.type = ARGUMENT;
	ft_export(pipeline, envs, &new_token);
	free(new_token.value);
}

static void	handle_invalid_path(t_pipeline *pipeline, t_envs_lst **envs,
	char *path_to_go)
{
	pipeline->exit_status = ER_MAIN;
	ft_putstr_fd(ft_search_env_var(envs, "USER"), STDERR_FILENO);
	ft_putstr_fd(": cd: ", STDERR_FILENO);
	ft_putstr_fd(path_to_go, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
}

static void	update_paths(t_pipeline *pipeline, t_envs_lst **envs,
	char *old_path, char *new_path)
{
	update_old_path(pipeline, envs, old_path);
	update_new_path(pipeline, envs, new_path);
}

void	ft_cd(t_pipeline *pipeline, t_envs_lst **envs, t_token *token)
{
	char	old_path[PATH_MAX + 1];
	char	new_path[PATH_MAX + 1];
	char	*status;

	status = getcwd(old_path, PATH_MAX + 1);
	if (status == NULL)
		ft_path_error();
	if (token == NULL)
	{
		if (ft_handle_empty_path(pipeline, envs) == false)
			return ;
	}
	else
	{
		if (chdir(token->value) == -1)
			return (handle_invalid_path(pipeline, envs, token->value));
	}
	status = getcwd(new_path, PATH_MAX + 1);
	if (status == NULL)
		ft_path_error();
	update_paths(pipeline, envs, old_path, new_path);
	pipeline->exit_status = ER_NON;
}





/* 

int main() {
    // Initialize a pipeline
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    if (pipeline == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
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

    // Initialize environment variables list
    t_envs_lst *envs = malloc(sizeof(t_envs_lst));
    if (envs == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }
    envs->data = NULL;
    envs->next = NULL;

    // Add initial environment variables manually
    t_variable *pwd_var = malloc(sizeof(t_variable));
    if (pwd_var == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }
    pwd_var->name = strdup("PWD");
    pwd_var->value = strdup("/home/user");
    pwd_var->next = NULL;

    t_variable *oldpwd_var = malloc(sizeof(t_variable));
    if (oldpwd_var == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }
    oldpwd_var->name = strdup("OLDPWD");
    oldpwd_var->value = strdup("/home/user/old");
    oldpwd_var->next = NULL;

    envs->data = pwd_var;
    pwd_var->next = oldpwd_var;

    // Test ft_cd with a relative path
    printf("Before cd:\n");
    printf("PWD=%s\n", ft_search_env_var(&envs, "PWD"));
    printf("OLDPWD=%s\n", ft_search_env_var(&envs, "OLDPWD"));
    printf("\n");

    t_token *token1 = malloc(sizeof(t_token));
    if (token1 == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }
    token1->type = ARGUMENT;
    token1->value = "test"; // Replace this with your desired directory
    token1->prev = NULL;
    token1->next = NULL;

    ft_cd(pipeline, &envs, token1);

    printf("After cd:\n");
    printf("PWD=%s\n", ft_search_env_var(&envs, "PWD"));
    printf("OLDPWD=%s\n", ft_search_env_var(&envs, "OLDPWD"));

    // Free allocated memory
    free(pipeline);
    free(pwd_var->name);
    free(pwd_var->value);
    free(pwd_var);
    free(oldpwd_var->name);
    free(oldpwd_var->value);
    free(oldpwd_var);
    free(token1);

    return 0;
} */