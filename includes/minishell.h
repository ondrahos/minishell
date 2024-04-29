/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:57:32 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/04/29 18:07:57 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <stdbool.h>
# include <fcntl.h>
# include <limits.h>
# include <linux/limits.h>
# include <termios.h>

# define ER_NON 0
# define ER_MAIN 1
# define ER_MAL 2
# define ER_PATH 3
# define ER_EXIT 4

typedef enum e_type
{
	COMMAND = 1,
	ARGUMENT = 2,
	IN_FILE = 3,
	OUT_FILE = 4,
	R_IN = 5,
	R_OUT = 6,
	HEREDOC = 7,
	APPEND = 8,
	DELIMITER = 9
}	t_type;

typedef struct s_data
{
	int		**pipes;
	int		*pids;
	int		pipe_count;
	char	**envp;
	int		original_stdin;
	int		original_stdout;
	int		status;
}	t_data;

typedef struct s_variable
{
	char				*name;
	char				*value;
	struct s_variable	*next;
}	t_variable;

typedef struct s_token
{
	int				type;
	char			*value;
	bool			free;
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

//parser
char		**pipe_split(char const *s, char c);
t_pipeline	*new_pipeline(void);
void		init_pipeline(t_pipeline *pipeline);
int			load_pipeline(char **line, t_pipeline **pipeline);
void		tokenize_pipeline(t_pipeline **pipeline);
void		load_token(char **line, t_token **token);
t_token		*new_token(void);
void		init_token(t_token *token);
void		assign_type(char **line, t_token **token, t_pipeline *s_pipeline);
void		expansion(t_pipeline **pipeline, t_variable **variable);
char		*get_var(char *value, t_variable **variable);
int			get_size(char *str);
bool		is_whitespace(char c);
bool		is_var(char *value);
bool		is_redir(char c);
bool		is_heredoc(char *s);
bool		is_delimiter(char *s);
char		**splitter(char *s);
int			handle_quotes(t_pipeline **pipeline);
void		load_variable(t_variable **variable, char **envp);
char		*ft_getenv(char *name, t_variable **variable);
int			handle_files(t_pipeline **pipeline, int i);
int			check_pipes(char *line);
int			check_syntax(t_pipeline **pipeline);
bool		is_quote(char c);
bool		is_in_squotes(char *s, int position);
bool		is_alphanum(char c);
int			get_name_len(char *s);
void		replace_value(char *tmp, t_token *token, bool free_var, char *var);
char		*allocate_memory(char *var, char *value);
char		*get_var_name(char *envp);
char		*get_var_value(char *envp);
int			open_heredoc(t_pipeline *pipeline, char *eof);
bool		has_quotes(char *s);
int			check_quotes(t_token *token);
void		remove_quotes(t_token *token);

//executer
int			count_pipes(t_pipeline **pipeline);
int			**allocate_pipes(int pipeline_count);
int			*allocate_pids(int pipeline_count);
int			execute(t_pipeline **pipeline, t_data data,
				int i, t_variable **variable);
void		close_pipes(int **pipes, int num);
void		execute_one(t_pipeline **pipeline, t_data *data,
				t_variable **variable);
void		dup_io(t_pipeline **pipeline, int i);
void		reset_io(int original_stdin, int original_stdout);
void		data_init(t_data *data, char **envp, t_pipeline **pipeline);
char		*get_path(t_pipeline *pipeline, t_variable **variable);
char		**get_cmd(t_pipeline *pipeline);
int			count_tokens(char *s);
bool		check_buildin(char **cmd, t_variable **variable,
				t_pipeline *pipeline, int pipe_count);
void		executer(t_pipeline **pipeline, t_variable **variable, char **envp);

//cleanup
void		free_pipeline(t_pipeline **pipeline);
void		free_array(char **arr);
void		*free_lines(char **s, int i);
void		free_data(t_data *data);
void		free_variable(t_variable **variable);

//build-ins
void		ft_cd(t_pipeline *pipeline, t_variable **envs, char **cmd);
void		ft_echo(char **cmd, t_pipeline *pipeline);
void		ft_env(t_pipeline *pipeline, t_variable **envs);
void		ft_exit(t_pipeline *pipeline,
				t_variable **envs, char **cmd, int pipe_count);
void		ft_export(t_pipeline *pipeline, t_variable **envs, char **cmd);
void		ft_pwd(t_pipeline *pipeline);
void		ft_unset(t_pipeline *pipeline, t_variable **envs, char **cmd);
void		update_status(int status, t_variable **variable);
void		check_pipeline_status(t_data *data, t_pipeline **pipeline);
int			safe_fork(t_data *data, int i);

//env syntax
bool		ft_check_env_syntax(char *value);

//env utils
void		ft_path_error(void);
void		ft_malloc_error(void);
char		*ft_search_env_var(t_variable **envs, char *name);
void		ft_remove_env_var(t_variable **envs, char *name);
void		ft_add_env_var(t_variable **envs, char *line);

//export
void		ft_export(t_pipeline *pipeline, t_variable **envs, char **cmd);
void		ft_handle_export_error(t_pipeline *pipeline,
				t_variable **envs,	char *arg);
char		**ft_get_sorted_keys(t_variable **envs);
void		ft_free_sorted_keys(char **keys, int size);

//cd
bool		ft_handle_empty_path(t_pipeline *pipeline, t_variable **envs);
void		ft_handle_invalid_path(t_pipeline *pipeline,
				t_variable **envs,	char *path_to_go);

//signals
void		ft_tty_mask(void);
void		ft_c_handle(int sig);
void		ft_c_handle_fork(int sig);
void		ft_slash_handle_fork(int sig);
void		ft_start_signals(void);
void		ft_set_signals(char **cmd);
void		ft_sig_empty(int sig);
void		ft_sig_heredoc(int sig);
void		ft_sig_ignore(int sig);

#endif
