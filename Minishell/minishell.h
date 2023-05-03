/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 09:43:59 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/03 14:36:18 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
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

# define ERR_NO_FILE_OR_DIR 1
# define ERR_SYNTAX 2

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
	t_file_datas				*input_lst;
	t_file_datas				*output_lst;
	struct s_pipe_node			*next;
}	t_pipe_node;

/* SHELL INFO */

typedef struct s_shell_infos
{
	struct termios		*term;
	struct sigaction	*sigint_processing;
	struct sigaction	*sigquit_processing;
	char				**envp;
	char				*name;
	char				*input;
	int					fd_opened;
	t_token				*token_lst;
	t_pipe_node			*pipe_lst;
}	t_shell;

/* ERROR HANDLING */

void		free_and_print_strerror(t_shell *shell);
void		free_and_print_custom_error(t_shell *shell, char *minishell_error);

/*EXECUTION*/

/*EXPAND*/

char		*expander(t_shell *shell, char *str);
char		*search_and_expand_env_var(t_shell *shell, char *str);

/*EXPORT*/

int			export(t_shell *shell, char *var);
int			get_export_mode(char *var);
int			check_export_variable_validity(char *var);
int			export_variable_is_in_envp(t_shell *shell, char *var, char c);
char		*get_value_to_append(t_shell *shell, char *var);

/*FREE MEMORY*/

void		free_shell(t_shell *shell);
void		free_pipe_lst(t_shell *shell);
void		free_token_lst(t_shell *shell);
t_token		*free_token_lst_without_content(t_token *lst);
void		free_and_print_custom_message(t_shell *shell, char *message);

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

char		*ft_strjoin_protected(t_shell *shell, char *s1, char *s2);
char		*get_string_from_fd(t_shell *shell, int fd);
void		close_fd(t_shell *shell, int fd);
void		shell_fd_control(t_shell *shell, char operation, int i);
void		update_exit_status_with_errno(t_shell *shell);

/* TEMP FUNCTIONS */

void		print_token_list_infos(t_token *lst);
void		print_fd_content(int fd);
void		print_pipe_lst_content(t_pipe_node *pipe_lst);

#endif
