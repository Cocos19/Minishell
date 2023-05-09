/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 09:43:59 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/09 15:35:12 by cmartino         ###   ########.fr       */
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

# define EPERM 1 // Operation not permitted
# define ERR_SYNTAX 2 //ENOENT = No Such file or directory
# define EMFILE 24 // Too may file open
# define EOWNER_DEAD 130 //Owner died (SIGINT)

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
	int							fdio[2];
	int							fd[2];
	t_file_datas				*input_file_lst;
	t_file_datas				*output_file_lst;
	struct s_pipe_node			*next;
}	t_pipe_node;

// execution
// if node->arguments[1] exist -> execute argv tab and nothing else (but you still have to open close inputs)
// else if node->input_file_lst exist -> execute only last input (but you still have to open close all others inputs)
// else if fd_in -> execute fd_in (fd_in = result of the pipe before)
// else execute without arg
// execution output
// if node->node->output_file_lst -> write in last output_file but you have to open/create all files then write to the last one
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
	t_token				*token_lst;
	t_pipe_node			*pipe_lst;
}	t_shell;

/*ECHO*/

void	builtin_echo(t_shell *shell, t_pipe_node *node, int fd_out);

/* ENV */

/* ERROR HANDLING */

void		free_and_print_strerror(t_shell *shell);
void		free_and_print_custom_error(t_shell *shell, char *minishell_error);

/*EXECUTION*/

int		ft_fork(t_shell *shell);
void	ft_pipe(t_shell *shell, t_pipe_node *pipe);
void	ft_dup2(t_shell *shell, int fd, int input);
void	open_close_inputs(t_shell *shell, t_file_datas *input_lst);
void	open_close_outputs(t_file_datas *output_lst);
int		write_to_outputs(char *result, t_file_datas *output_lst);

char	*cmd_exist(char **envp, char **arg);
void	execution(t_shell *shell);
char	**get_envp_paths(char **envp);
void	free_all_tab(char **p_tab, int len);

/*EXPAND*/

char		*expander(t_shell *shell, char *str);
char		*search_and_expand_env_var(t_shell *shell, char *str);

/*EXPORT*/

int			export(t_shell *shell, char *var);
int			get_export_mode(char *var);
int			check_export_variable_validity(char *var);
int			export_variable_is_in_envp(t_shell *shell, char *var, char c);
char		*get_value_to_append(t_shell *shell, char *var);
void		builtin_export(t_shell *shell, t_pipe_node *node);

/*FREE MEMORY*/

void	free_shell(t_shell *shell);
void	free_pipe_lst(t_shell *shell);
void	free_token_lst(t_shell *shell);
t_token	*free_token_lst_without_content(t_token *lst);
void	free_and_print_custom_message(t_shell *shell, char *message);

/* HEREDOC */

int			get_heredoc(t_shell *shell, char *delimiter);
//INFO FOR PARSING: Function return a fd opened in order to read the heredoc.
//If SIGINT is triggered, the function still return a fd ready to read.
//It must be checked and closed if this happened
//The error should be handled, the exit status stored
//and then g_exit_status should be setup at 0 again

/* PARSING */

void		parser(t_shell *shell);
t_pipe_node	*init_pipe_node(t_shell *shell);
t_token		*get_arg(t_shell *shell, t_token *arg_list, t_token *token);
char		**init_argument_array(t_shell *shell, t_token *arg_list);
int			next_token_is_valid(t_shell *shell, t_token *token);
t_token		*get_input(t_shell *shell, t_pipe_node *cur_n, t_token *cur_token);
t_token		*get_output(t_shell *shell, t_pipe_node *cur_n, t_token *cur_token);

/* PROMPT */

char		*give_prompt(t_shell *shell);
int			input_is_valid(t_shell *shell);

/* SIGNALS HANDLING */

void		sigint_shell_h(int signal_id, siginfo_t *sig_info, void *context);
void		nosigint_shell_h(int signal_id, siginfo_t *sig_info, void *context);
void		sigint_hered_h(int signal_id, siginfo_t *sig_info, void *context);
void		sigquit_shell_h(int signal_id, siginfo_t *sig_info, void *context);
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
int			is_special_character(char c);
t_token		*init_token(t_shell *shell);
t_token		*tokenize(t_shell *shell, char *input);
int			token_list_is_valid(t_shell *shell);
char		*get_pipe(t_shell *shell, char *input, t_token *cur, char *start);
char		*get_redir(t_shell *shell, char *input, t_token *cur, char *start);
void		complete_token(t_shell *shell);

/* UTILS */

char	*ft_strjoin_protected(t_shell *shell, char *s1, char *s2);
char	*get_string_from_fd(t_shell *shell, int fd);
int		len_tab(char **tb);
int		ft_lstsize_pipe(t_pipe_node *lst);
int	ft_open_infiles(t_shell *shell, t_pipe_node *pipe);
int	ft_open_outfiles(t_shell *shell, t_pipe_node *pipe);
void	ft_close_files(int fd, char *name);
void	ft_close(int fd);
int	*create_pids(t_pipe_node *pipe);
// void	update_exit_status_with_errno(t_shell *shell);

/* TEMP FUNCTIONS */

void		print_token_list_infos(t_token *lst);
void		print_fd_content(int fd);
void		print_pipe_lst_content(t_shell *shell, t_pipe_node *pipe_lst);

#endif
