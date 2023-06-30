/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 09:43:59 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/29 14:33:03 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <term.h>
# include <unistd.h>

/* GLOBAL VARIABLE */

int	g_exit_status;

/* ERROR MACROS */

# define EPERM 1
# define ERR_SYNTAX 2
# define COMMAND_NOT_FOUND 127
# define EOWNER_DEAD 130
# define INTERRUPTED_BY_SIGNAL 131

# define DEFAULT_MODE 1
# define HEREDOC_MODE 2
# define CHILD_MODE 3
# define IGNORE_MODE 4

typedef struct s_token
{
	char				*value;
	struct s_token		*last;
	struct s_token		*next;
}	t_token;

typedef struct s_redir_datas
{
	int						mode;
	char					*value;
	char					type;
	struct s_redir_datas	*last;
	struct s_redir_datas	*next;
}	t_redir_datas;

typedef struct s_pipe_node
{
	char						**arguments;
	char						*path;
	int							*pids;
	int							fdio[2];
	int							iofiles[2];
	int							dup_stdout;
	t_redir_datas				*in_out_redir_list;
	struct s_pipe_node			*next;
}	t_pipe_node;

/* SHELL INFO */

typedef struct s_shell_infos
{
	char				**envp;
	char				*name;
	char				*input;
	int					last_exit_status;
	int					exit;
	int					*pids;
	int					**pipefd;
	int					nbr_cmds;
	t_token				*token_lst;
	t_pipe_node			*pipe_lst;
}	t_shell;

/*BUILTIN*/

int			builtin_cd(t_shell *shell, t_pipe_node *node);
char		*get_dot_relative_path(t_shell *shell, t_pipe_node *node);
char		*get_home_relative_path(t_shell *shell, char *arg);
int			get_old_pwd_path(t_shell *shell);
void		update_env_var(t_shell *shell, char *to_update, char *new_val);
int			builtin_echo(t_shell *shell, t_pipe_node *node);
int			builtin_env(t_shell *shell, t_pipe_node *node);
int			builtin_export(t_shell *shell, t_pipe_node *node);
void		single_cmd_builtin_exit(t_shell *shell, t_pipe_node *node);
int			builtin_exit(t_shell *shell, t_pipe_node *node);
int			builtin_pwd(void);
int			builtin_unset(t_shell *shell, t_pipe_node *node);
int			redirection_builtin(t_shell *shell, t_pipe_node *pipe);
int			is_builtin(t_pipe_node *pipe);

/* ERROR HANDLING */

void		print_str_error_and_exit(void);
void		print_info_str_error_and_exit(char *info);
void		print_info_and_exit(char *info, int exit_status);
void		print_builtin_info_str_error_and_exit(char *builtin, char *info);

/*EXECUTION*/

int			ft_fork(t_shell *shell);
void		ft_dup2(t_shell *shell, int fd, int input);
char		*cmd_exist(t_shell *shell, char **envp, char **arg);
void		execution(t_shell *shell);
char		**get_envp_paths(char **envp);
void		free_all_tab(char **p_tab, int len);
void		execution(t_shell *shell);
char		**get_envp_paths(char **envp);
void		free_all_tab(char **p_tab, int len);
void		ft_waitpids(t_shell *shell);
void		execution_single_builtin(t_shell *shell, t_pipe_node *cmd);
void		first_cmd(t_shell *shell, t_pipe_node *cmd);
void		middle_cmd(t_shell *shell, t_pipe_node *cmd, int i);
void		last_cmd(t_shell *shell, t_pipe_node *cmd, int i);
void		find_path(t_shell *shell, t_pipe_node *pipe);

/*EXPAND*/

char		*expander(t_shell *shell, char *str);
char		*search_and_expand_env_var(t_shell *shell, char *str);
char		*is_an_envp_var(t_shell *shell, char *str);

/*ENVIRONNEMENT VARIABLES*/

int			export(t_shell *shell, char *var);
int			get_export_mode(char *var);
int			check_export_variable_validity(char *var);
int			export_variable_is_in_envp(t_shell *shell, char *var, char c);
char		*get_value_to_append(char *var);

/*FREE MEMORY UTILS*/

void		free_shell(t_shell *shell);
void		free_pipe_lst(t_shell *shell);
void		free_token_lst(t_shell *shell);
t_token		*free_arg_lst(t_token *lst);
void		free_and_print_custom_message(t_shell *shell, char *message);
int			**ft_free_all(int **array, size_t j);
void		ft_free_execution(t_shell *shell);

/* HEREDOC */

int			get_heredoc(t_shell *shell, char *delimiter);

/* PARSING */

void		parser(t_shell *shell);
char		**init_argument_array(t_token *arg_list);
t_pipe_node	*init_pipe_node(void);
t_token		*get_arg(t_shell *shell, t_token *arg_list, t_token *token);
t_token		*get_input(t_shell *shell, t_pipe_node *cur_n, t_token *cur_token);
t_token		*get_output(t_shell *shell, t_pipe_node *cur_n, t_token *cur_token);
int			next_token_is_valid(t_shell *shell, t_token *token);

/* PROMPT */

char		*give_prompt(t_shell *shell);
int			input_is_valid(t_shell *shell);

/* SIGNALS HANDLING */

void		activate_signals(int mode);

/* TOKENS */

void		lexer(t_shell *shell, char *user_input);
void		complete_token(t_shell *shell);
char		*get_pipe(char *input, t_token *cur, char *start);
char		*get_redir(char *input, t_token *cur, char *start);
t_token		*init_token(void);
t_token		*tokenize(char *input);
int			is_special_character(char c);
int			token_list_is_valid(t_shell *shell);

/* UTILS */

char		*ft_strjoin_protected(char *s1, char *s2);
char		*get_string_from_fd(int fd);
int			len_tab(char **tb);
int			lstsize_cmd(t_pipe_node *cmd);
int			ft_open_infile(t_shell *shell, t_redir_datas *input_lst);
int			ft_open_outfile(t_shell *shell, t_redir_datas *output_lst);
void		ft_close(int fd, char *msg);
void		ft_close_parent(int pos, t_pipe_node *cmd, t_shell *shell);
void		create_pids(t_shell *shell, t_pipe_node *pipe);
void		ft_exit_cmd(t_shell *shell, int exit_code);
void		openiofile(t_shell *shell, t_pipe_node *pipe, t_redir_datas *files);

/* TEMP FUNCTIONS */

void		print_token_list_infos(t_token *lst);
void		print_fd_content(int fd);
void		print_pipe_lst_content(t_shell *shell, t_pipe_node *pipe_lst);
void		print_redir_datas_lst(t_redir_datas *datas_lst);

void		find_path(t_shell *shell, t_pipe_node *pipe);
int			*create_mini_pipe(void);
int			**init_pipes(int nbr_pipes);
int			ft_pipe(int **array, int pos);

#endif
