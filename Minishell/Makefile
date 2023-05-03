# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/17 09:47:54 by mprofett          #+#    #+#              #
#    Updated: 2023/04/24 15:21:00 by mprofett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

SRC			= minishell.c minishell_execute.c minishell_free.c \
			minishell_prompt.c minishell_parser_heredoc.c \
			minishell_expander.c minishell_parser.c \
			minishell_parser_arguments.c minishell_signals.c \
			minishell_utils.c minishell_temp.c minishell_terminal.c \
			minishell_lexer_special_tokens.c \
			minishell_lexer_checker.c minishell_builtin_export.c minishell_lexer.c \
			minishell_parser_redirections.c minishell_expander_env_var.c \
			minishell_signals_activation.c \

SRC_BONUS	=

OBJ			= ${SRC:.c=.o}

OBJ_BONUS	= ${SRC_BONUS:.c=.o}

LIBFT		= libft.a

LIBFT_PATH	= libft

CC			= gcc

RM			= rm -f

C_FLAGS	= -Wall -Wextra -Werror

%.o: %.c
	$(CC) $(C_FLAGS) -I/Users/mprofett/.brew/opt/readline/include -c $< -o $@

all: ${NAME}

${NAME}: ${OBJ} ${LIBFT}
	${CC} ${OBJ} -o  ${NAME} ${LIBFT} -I/Users/mprofett/.brew/opt/readline/include -L/Users/mprofett/.brew/opt/readline/lib -lreadline -fsanitize=address

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
