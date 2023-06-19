/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 09:43:59 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/19 15:43:52 by mprofett         ###   ########.fr       */
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
# define EOWNER_DEAD 130

typedef struct s_token
{
	char				*value;
	struct s_token		*last;
	struct s_token		*next;
}	t_token;

/* PIPE NODES */

typedef struct s_file_datas
{
	int					mode;
	char				*value;
	struct s_file_datas	*last;
	struct s_file_datas	*next;
}	t_file_datas;

typedef struct s_pipe_node
{
	char						**arguments;
	char						*path;
	int							*pids;
	int							fdio[2];
	int							fd[2];
	t_file_datas				*input_file_lst;
	t_file_datas				*output_file_lst;
	struct s_pipe_node			*next;
}	t_pipe_node;

// execution
// if node->arguments[1] exist -> execute argv tab and nothing else
// but you still have to open close inputs
// else if node->input_file_lst exist -> execute only last input
// but you still have to open close all others inputs
// else if fd_in -> execute fd_in (fd_in = result of the pipe before)
// else execute without arg
// execution output
// if node->node->output_file_lst -> write in last output_file
// but you have to open/create all files then write to the last one
// else if node->next -> write in fd_out
// else write in stdout
// update shell->last_exit_status

/* SHELL INFO */

typedef struct s_shell_infos
{
	struct termios		*term;
	struct sigaction	*sigint_processing;
	struct sigaction	*sigquit_processing;
	char				**envp;
	char				*name;
	char				*input;
	int					last_exit_status;
	int					*pids;
	t_token				*token_lst;
	t_pipe_node			*pipe_lst;
}	t_shell;

/*BUILTIN*/

/*How to use builtin
if builtin are single command, it should be launched in a fork
exit is handled by a single function before exec function so no needed to handle it when exit is single command
builtin never close fds so its the exec function responsability to close it
builtin function have different behaviour when in pipe chain or not so some of them need to know it
in this purpose some builtin need a fd_in and fd_out
if the command is the first node of pipe chain, fd_in should be -1
if the commad is the last node of pipe chain, fd_out should be 1 (STDOUT)
we should not forget that if -1 or 1 is passed as fd argument it shouldnt be closed
*/

int			builtin_cd(t_shell *shell, t_pipe_node *node);
int			builtin_echo(t_shell *shell, t_pipe_node *node);
int			builtin_env(t_shell *shell, t_pipe_node *node);
int			builtin_export(t_shell *shell, t_pipe_node *node);
void		single_cmd_builtin_exit(t_shell *shell, t_pipe_node *node);
int			builtin_exit(t_shell *shell, t_pipe_node *node);
int			builtin_pwd(t_shell *shell, t_pipe_node *node);
int			builtin_unset(t_shell *shell, t_pipe_node *node);
int			redirection_buitin(t_shell *shell, t_pipe_node *pipe);

/* ERROR HANDLING */

void		print_str_error_and_exit(void);
void		print_info_str_error_and_exit(char *info);
void		print_info_and_exit(char *info, int exit_status);
void		print_builtin_info_str_error_and_exit(char *builtin, char *info);

/*EXECUTION*/

int			ft_fork(t_shell *shell);
void		ft_pipe(t_shell *shell, t_pipe_node *pipe);
void		ft_dup2(t_shell *shell, int fd, int input);
// void		open_close_inputs(t_shell *shell, t_file_datas *input_lst);
// void		open_close_outputs(t_file_datas *output_lst);
// int			write_to_outputs(char *result, t_file_datas *output_lst);
// int			write_array_to_outputs(char **result, t_file_datas *output_lst);
int			open_close_inputs(t_shell *shell, t_file_datas *input_lst);
int			open_close_outputs(t_file_datas *output_lst);
int			write_to_outputs(char *result, t_file_datas *output_lst);
int			write_array_to_outputs(char **result, t_file_datas *output_lst);

char	*cmd_exist(char **envp, char **arg);
void	execution(t_shell *shell);
char	**get_envp_paths(char **envp);
void	free_all_tab(char **p_tab, int len);

char	*cmd_exist(char **envp, char **arg);
void	execution(t_shell *shell);
char	**get_envp_paths(char **envp);
void	free_all_tab(char **p_tab, int len);
void	ft_waitpids(t_shell *shell, t_pipe_node *pipe);
void	execution_one_cmd(t_shell *shell, t_pipe_node *pipe);
void	first_cmd(t_shell *shell, t_pipe_node *pipe);
void	middle_cmd(t_shell *shell, t_pipe_node *pipe, int i);
void	last_cmd(t_shell *shell, t_pipe_node *pipe, int i);
void	find_path(t_shell *shell, t_pipe_node *pipe);

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
void		free_file_datas_list(t_file_datas *lst);
t_token		*free_arg_lst(t_token *lst);
void		free_and_print_custom_message(t_shell *shell, char *message);

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

void		sigquit_shell_h(int signal_id, siginfo_t *sig_info, void *context);
void		sigint_shell_h(int signal_id, siginfo_t *sig_info, void *context);
void		nosigint_shell_h(int signal_id, siginfo_t *sig_info, void *context);
void		sigint_hered_h(int signal_id, siginfo_t *sig_info, void *context);
void		act_sint_handler(t_shell *shell, void f(int, siginfo_t *, void *));
void		desact_sint_handler(t_shell *shell);
void		act_squit_handler(t_shell *shell, void f(int, siginfo_t *, void *));
void		desact_squit_handler(t_shell *shell);

/* TERMINAL */

void		init_terminal(t_shell *shell, char **envp);
void		act_vquit(t_shell *shell);
void		desact_vquit(t_shell *shell);

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
int		len_tab(char **tb);
int		ft_lstsize_pipe(t_pipe_node *lst);
int	ft_open_infiles(t_shell *shell, t_pipe_node *pipe);
int	ft_open_outfiles(t_shell *shell, t_pipe_node *pipe);
void	ft_close_files(int fd, char *name);
void	ft_close(int fd);
void	create_pids(t_shell *shell, t_pipe_node *pipe);
void	ft_copy_fd(t_pipe_node *pipe);
// void	update_exit_status_with_errno(t_shell *shell);

/* TEMP FUNCTIONS */

void		print_token_list_infos(t_token *lst);
void		print_fd_content(int fd);
void		print_pipe_lst_content(t_shell *shell, t_pipe_node *pipe_lst);

#endif
