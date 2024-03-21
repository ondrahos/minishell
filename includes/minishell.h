/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:57:32 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/03/21 15:17:16 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/readline.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <stdbool.h>
# include <fcntl.h>

typedef enum	e_type
{
	COMMAND = 1,
	ARGUMENT = 2,
	IN_FILE = 3,
	OUT_FILE = 4,
	R_IN = 5,
	R_OUT = 6,
	HEREDOC = 7,
	APPEND = 8,
	DELIMITER = 9,
}	t_type;

typedef struct s_variable
{
	char				*name;
	char				*value;
	struct s_variable	*next;
}	t_variable;


typedef struct	s_token
{
	int				type;
	char			*value;
	bool			free;
	struct s_token	*next;
}	t_token;


typedef struct	s_pipeline
{
	char				**line;
	int					in_fd;
	int					out_fd;
	char				*here_doc;
	bool				append;
	t_token				*token;
	struct s_pipeline	*next;
}	t_pipeline;

t_pipeline	*new_pipeline(void);
void		init_pipeline(t_pipeline *pipeline);
void		load_pipeline(char **line, t_pipeline **pipeline);
void		tokenize_pipeline(t_pipeline **pipeline);
void		free_pipeline(t_pipeline **pipeline);
void		free_array(char **arr);
void		load_token(char **line, t_token **token);
t_token		*new_token(void);
void		init_token(t_token *token);
void		assign_type(char **line, t_token **token,  t_pipeline *s_pipeline);
void		expansion(t_pipeline **pipeline, t_variable **variable);
void		expand_var(t_token *token, t_variable **variable);
char		*get_var(char *value, t_variable **variable);
int			get_size(char *str);
bool		is_whitespace(char c);
bool		is_var(char *value);
void		*free_lines(char **s, int i);
bool		is_redir(char c);
bool		is_heredoc(char *s);
bool		is_delimiter(char *s);
char		**splitter(char *s);
int			handle_quotes(t_pipeline **pipeline);
void		load_variable(t_variable **variable, char **envp);
void		free_variable(t_variable **variable);
char		*ft_getenv(char *name, t_variable **variable);
int			handle_files(t_pipeline **pipeline);


#endif
