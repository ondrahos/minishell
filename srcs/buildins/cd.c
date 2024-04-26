/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 10:38:02 by daraz             #+#    #+#             */
/*   Updated: 2024/04/23 20:48:34 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_old_path(t_pipeline *pipeline, t_variable **envs, char *old_path)
{
	char	**old_pwd;

	old_pwd = malloc(sizeof(char *) * 3 + 1);
	if (old_pwd == NULL)
		ft_malloc_error();
	old_pwd[2] = NULL;
	ft_remove_env_var(envs, "OLDPWD");
	old_pwd[0] = ft_strdup("export");
	old_pwd[1] = ft_strjoin("OLDPWD=", old_path);
	if (old_pwd == NULL)
		ft_malloc_error();
	ft_export(pipeline, envs, old_pwd);
	free_array(old_pwd);
}

static void	update_new_path(t_pipeline *pipeline, t_variable **envs, char *new_path)
{
	char	**new_pwd;

	new_pwd = malloc(sizeof(char *) * 3 + 1);
	if (new_pwd == NULL)
		ft_malloc_error();
	new_pwd[2] = NULL;
	ft_remove_env_var(envs, "PWD");
	new_pwd[0] = ft_strdup("export");
	new_pwd[1] = ft_strjoin("PWD=", new_path);
	if (new_pwd == NULL)
		ft_malloc_error();
	ft_export(pipeline, envs, new_pwd);
	free_array(new_pwd);
}

static void	update_paths(t_pipeline *pipeline, t_variable **envs,
	char *old_path, char *new_path)
{
	update_old_path(pipeline, envs, old_path);
	update_new_path(pipeline, envs, new_path);
}

void	ft_cd(t_pipeline *pipeline, t_variable **envs, char **cmd)
{
	char	old_path[PATH_MAX + 1];
	char	new_path[PATH_MAX + 1];
	char	*status;

	status = getcwd(old_path, PATH_MAX + 1);
	if (status == NULL)
		ft_path_error();
	if (cmd[1] == NULL)
	{
		if (ft_handle_empty_path(pipeline, envs) == false)
			return ;
	}
	else
	{
		if (chdir(cmd[1]) == -1)
			return (ft_handle_invalid_path(pipeline, envs, cmd[1]));
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
