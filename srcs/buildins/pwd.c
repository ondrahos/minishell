/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daraz <daraz@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:43:28 by daraz             #+#    #+#             */
/*   Updated: 2024/03/29 14:12:59 by daraz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "build.h"

void	ft_pwd(t_pipeline *pipeline)
{
	char	pwd[PATH_MAX + 1];
	char	*status;

	pipeline->exit_status = ER_NON;
	status = getcwd(pwd, PATH_MAX + 1);
	if (status == NULL)
		return ;
	write(STDOUT_FILENO, pwd, ft_strlen(pwd));
	write(STDOUT_FILENO, "\n", 1);
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
	
    ft_pwd(pipeline);

	free(pipeline);
    
    return 0;
} */