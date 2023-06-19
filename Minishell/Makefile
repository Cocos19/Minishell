# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/17 09:47:54 by mprofett          #+#    #+#              #
#    Updated: 2023/06/19 10:51:19 by mprofett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

SRC			= minishell.c \
			minishell_prompt.c minishell_parser_heredoc.c \
			minishell_expander.c minishell_parser.c \
			minishell_parser_arguments.c minishell_signals.c \
			minishell_temp.c minishell_terminal.c \
			minishell_lexer_special_tokens.c \
			minishell_lexer_checker.c minishell_lexer.c \
			minishell_parser_redirections.c minishell_expander_env_var.c \
			minishell_signals_activation.c \
			builtin/cd.c \
			builtin/echo.c \
			builtin/env.c \
			builtin/exit.c \
			builtin/export.c \
			builtin/export_exec.c \
			builtin/export_utils.c \
			builtin/pwd.c \
			builtin/unset.c \
			builtin/redirection_builtin.c \
			execution/cmd_execution.c \
			execution/cmd_exist.c \
			execution/execution_one_cmd.c \
			execution/execution_first_cmd.c \
			execution/execution_middle_cmd.c \
			execution/execution_last_cmd.c \
			execution/get_envp.c \
			execution/waitpids.c \
			utils/free.c \
			utils/free_and_print_msg.c\
			utils/free_token_lst.c \
			utils/utils.c \
			utils/utils_execution.c \
			utils/utils_open_close.c \
			minishell_execution_redirections.c \

OBJ			= ${SRC:.c=.o}

OBJ_BONUS	= ${SRC_BONUS:.c=.o}

HOME		= $(shell echo $$HOME)

LIBFT		= libft.a

LIBFT_PATH	= libft

CC			= gcc

RM			= rm -f

C_FLAGS	= -Wall -Wextra -Werror

%.o: %.c
	$(CC) $(C_FLAGS) -I/${HOME}/.brew/opt/readline/include -c $< -o $@

all: ${NAME}

${NAME}: ${OBJ} ${LIBFT}
	${CC} ${OBJ} -o  ${NAME} ${LIBFT} -I ${HOME}/.brew/opt/readline/include -L/${HOME}/.brew/opt/readline/lib -lreadline -fsanitize=address

${LIBFT}:
	${MAKE} bonus -C ${LIBFT_PATH}
	mv ${LIBFT_PATH}/${LIBFT} .

bonus: ${OBJ_BONUS} ${LIBFT}
	${CC} ${OBJ_BONUS} -o  ${NAME} ${LIBFT}

clean:
	${MAKE} clean -C ${LIBFT_PATH}
	${RM} ${OBJ} ${OBJ_BONUS}

fclean: clean
	${RM} ${NAME} ${LIBFT}

re:	fclean all

.PHONY:	all bonus clean fclean re
