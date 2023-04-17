/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 09:43:59 by mprofett          #+#    #+#             */
/*   Updated: 2023/04/17 09:56:35 by mprofett         ###   ########.fr       */
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

//This global variable is needed as we cant transfer exit status info from signals
//Signals handler function doenst allow variable return

/* ERROR MACROS */

# define ERR_SYNTAX 2

/* TYPEDEF VARIABLES */

typedef struct s_local_variable
{
	char					*name;
	char					*value;
	struct s_local_variable	*last;
	struct s_local_variable	*next;
}	t_local_var;

typedef struct s_token
{
	char				*value;
	struct s_token		*next;
}	t_token;

/* PIPE NODES */

//The command structure is stored in a chained list of pipe_node
// A pipe node have several variables usefull for the execution
// - an argument list that will be given to the execve function
// - a tempvarlist that will stored all the token that should register a new local variable for the t_shell
// 	* this list will be used for registering local variable only at certain conditions;
// 		- there is only one node to execute (ex: a="variable" b="variable ...") but not this a="variable" | b="variable")
// 		- the content of the node is only made of locale variable to register have no input_file_list, no output_file_list, no argument
// - an input_list that will content all the input_file given to the command. Here are some spec:
// 	* The input_file given by heredoc have a char *name = NULL and will always have his fd already opened.
// 	* Bash will try to read any input_file given but it will only use the last of the list as input for the command. So he will try to open it even it wont use it
// 	* if an input_file doesnt exist, it will trow an error message (No such file or directory) and move on to the next pipe node
// 	The execution priority for input are:
// 	* So the execution will be:
// 		- check if there is an input from the fd from an parent pipe.
// 			if there is input_files in input_files_list, it will close the fd and dont use the content
// 		- check the input_file_list, try to open every named file it encounter
// 			each time there is an input_file->next, it will close the fd (wich was opened with the open function or already opened if there a NULL char *name (it's a heredoc result))
// 		- check if there is argument in argv[1] and more.
// 			if there is argument is there char **argv, it will close the last input_file too and use the argument in the char *argv)
// 			if there is arguments in char **argv, It will use all of them one after the other not juste the last
// - an output_list. Here are the priorities:
// 	- The exection will create any file needed to write output but will only write output in the last one. It will overwrite the content if the in_happend_mode == 0 or in happend_mode if == 1
// 	- If the output_list is empty, it will send the output in a pipe for the next pipe node
// 	- If there no new pipe_node, it will write the output in sdtout

typedef struct s_input_file_infos
{
	char						*name;
	int							fd;
	struct s_input_node_infos	*next;
} t_input_file;

typedef struct s_output_file_infos
{
	char						*name;
	int							in_happend_mode;
	struct s_output_file_infos	*next;
} t_output_file;

typedef struct s_pipe_node
{
	char				**arguments;
	t_local_var			*temp_varlist;
	t_input_file		*input_file_lst;
	t_input_file		*output_file_lst;
	struct s_pipe_node	*next;
}	t_pipe_node;

/* SHELL INFO */

typedef struct s_shell_infos
{
	struct termios		*term;
	struct sigaction	*signal_processing;
	t_local_var			*varloc_list;
	char				**envp;
	char				*name;
	char				*input;
	t_token				*token_lst;
}	t_shell;

/* ENV */

/* ERROR HANDLING */

void	free_and_print_strerror(t_shell *shell);
void	free_and_print_custom_error(t_shell *shell, char *minishell_error);

/*EXECUTION*/

/*EXPAND*/

/*FREE MEMORY*/

void	free_shell(t_shell *shell);
void	free_token_lst(t_token *lst);
void	free_and_print_custom_message(t_shell *shell, char *message);

/* HEREDOC */

int get_heredoc(t_shell *shell, char *delimiter);
//INFO FOR PARSING: Function return a fd opened in order to read the heredoc.
//If SIGINT is triggered, the function still return a fd ready to read. It must be checked and closed if this happened
//The error should be handled, the exit status stored and then g_exit_status should be setup at 0 again

/* INPUT VALIDITY */

int		input_is_valid(t_shell *shell);

/* LOCALE VARIABLE */

void	add_new_locale_variable(t_shell *shell, char *name, char *value);
void	update_exit_status_variable(t_shell *shell);

/* PIPE NODE LIST */

/* SIGNALS HANDLING */

void	sigint_shell_handler(int signal_id, siginfo_t *sig_info, void *context);
void	sigint_hered_handler(int signal_id, siginfo_t *sig_info, void *context);
void	sigint_handler_off(int signal_id, siginfo_t *sig_info, void *context);
void	activate_sigint_handler(t_shell *shell, void f(int, siginfo_t *, void *));

/* TERMINAL */

void	init_terminal(t_shell *shell);
void	activate_vquit(t_shell *shell);
void	desactivate_vquit(t_shell *shell);

/* TOKENS */

t_token	*tokenize(t_shell *shell, char *input);
char	*tokenize_pipe_operator(t_shell *shell, char *input, t_token *current, char *start);
char	*tokenize_redirection_operator(t_shell *shell, char *input, t_token *current, char *start);
char	*tokenize_quotes(t_shell *shell, char *input, t_token *current, char *start);

/* UTILS */

char	*ft_strjoin_protected(t_shell *shell, char *s1, char *s2);

/* TEMP FUNCTIONS */

//Thoses functions are here for debugging, they should be suppressed when the project is over

void	init_some_locales_variables(t_shell *shell);
void	print_token_list_infos(t_token *lst);
void	print_fd_content(int fd);

#endif
