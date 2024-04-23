/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daraz <daraz@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:25:42 by daraz             #+#    #+#             */
/*   Updated: 2024/04/23 12:42:13 by daraz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <linux/limits.h>
#include <signal.h>
#include <termios.h>
#include <asm-generic/termbits.h>

# define ARGUMENT 2
# define COMMAND = 1

# define ER_NON 0
# define ER_MAIN 1
# define ER_MAL 2
# define ER_PATH 3
# define ER_EXIT 4

typedef struct s_variable
{
	char				*name;
	char				*value;
	struct s_variable	*next; // ?
}	t_variable;



typedef struct s_envs_lst
{
	t_variable		*data;
	struct s_envs_lst	*next;
}	t_envs_lst;



typedef struct	s_token
{
	int				type;
	char			*value;
	bool			free;
	struct s_token  *prev;
	struct s_token	*next;
}	t_token;

typedef struct s_pipeline
{
	int					exit_status;
	char				**line;
	int					in_fd;
	int					out_fd;
	bool				here_doc;
	bool				append;
	t_token				*token;
	struct s_pipeline	*next;
}	t_pipeline;

//env syntax
bool	ft_check_env_syntax(char *value);

//env utils
void	ft_path_error(void);
void	ft_malloc_error(void);
char	*ft_search_env_var(t_envs_lst **envs, char *name);
void	ft_remove_env_var(t_envs_lst **envs, char *name);
void	ft_add_env_var(t_envs_lst **envs, char *line);
void	ft_free_envs(t_envs_lst **envs);

//libft
int	ft_isalnum(int c);
int	ft_isalpha(int c);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *str);
int	ft_isdigit(int c);
int	ft_atoi(const char *str);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);

//export
void	ft_export(t_pipeline *pipeline, t_envs_lst **envs, t_token *token);
void	ft_handle_export_error(t_pipeline *pipeline, t_envs_lst **envs,	t_token *token);
char	**ft_get_sorted_keys(t_envs_lst **envs);
void	ft_free_sorted_keys(char **keys, int size);

//cd
bool	ft_handle_empty_path(t_pipeline *pipeline, t_envs_lst **envs);
void	ft_handle_invalid_path(t_pipeline *pipeline, t_envs_lst **envs,	char *path_to_go);