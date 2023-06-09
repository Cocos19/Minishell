# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/17 09:47:54 by mprofett          #+#    #+#              #
#    Updated: 2023/07/05 09:26:55 by mprofett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

SRC			= main.c \
			builtin/cd.c \
			builtin/cd_utils.c \
			builtin/echo.c \
			builtin/env.c \
			builtin/exit.c \
			builtin/export.c \
			builtin/export_exec.c \
			builtin/export_utils.c \
			builtin/pwd.c \
			builtin/unset.c \
			execution/cmd_execution.c \
			execution/cmd_exist.c \
			execution/execution_single_builtin.c \
			execution/execution_first_cmd.c \
			execution/execution_middle_cmd.c \
			execution/execution_last_cmd.c \
			execution/ft_pipes.c \
			execution/ft_open_close.c \
			execution/get_envp.c \
			execution/waitpids.c \
			execution/open_infiles.c \
			execution/open_outfiles.c \
			execution/redirection_builtin.c \
			expander/expander.c \
			expander/env_var.c \
			lexer/lexer.c \
			lexer/special_tokens.c \
			parser/parser.c \
			parser/get_heredoc.c \
			parser/parse_arguments.c \
			parser/parse_redirections.c \
			prompt/prompt.c \
			signals/signals.c \
			utils/free.c \
			utils/exit_messages.c\
			utils/free_token_lst.c \
			utils/utils.c \
			utils/utils_open_close.c \
			utils/utils_execution.c \
			utils/ft_array.c \

OBJ			= ${SRC:.c=.o}

OBJ_BONUS	= ${SRC_BONUS:.c=.o}

LIBFT		= libft.a

HOME		= $(shell echo $$HOME)

LIBFT_PATH	= libft

CC			= gcc

RM			= rm -f

C_FLAGS	= -Wall -Wextra -Werror

%.o: %.c
	$(CC) $(C_FLAGS) -I/${HOME}/.brew/opt/readline/include -c $< -o $@

all: ${NAME}

${NAME}: ${OBJ} ${LIBFT}
	${CC} ${C_FLAGS} ${OBJ} -o  ${NAME} ${LIBFT} -I ${HOME}/.brew/opt/readline/include -L/${HOME}/.brew/opt/readline/lib -lreadline


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
