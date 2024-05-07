NAME			=	minishell

SRCS			=	src/minishell.c \
                    src/env.c \
					src/lexer.c \
					src/lexer_quotes.c        src/lexer_space_pipe.c    src/lexer_check.c \
					src/lexer_quotes_open.c   src/lexer_dollar.c \
					src/parser.c \
					src/exec.c \
					src/exec_path.c src/exec_fork.c \
					src/builtin.c \
					src/builtin_export.c      src/builtin_echo_cd_pwd.c  src/builtin_exit.c\
					src/builtin_export_args.c src/builtin_unset_env.c \
                    src/free.c \
					src/utils.c
				
OBJS = ${SRCS:.c=.o}

CC = gcc

CFLAGS = -Wall -Wextra -Werror 
LIB_MAC		= -lreadline -L/Users/adelaloy/.brew/Cellar/readline/8.2.7/lib
LIB_LINUX = -lreadline

RM = rm -f

all: ${NAME}

.c.o:
	${CC} ${CFLAGS} -I$(HOME)/.brew/Cellar/readline/8.2.7/include -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
ifeq ($(USER), anna)
	@make bonus -C ./libft
	$(CC) $(OBJS) $(CFLAGS) $(LIB_LINUX) libft/libft.a -o $(NAME)
else
	@make bonus -C ./libft
	$(CC) $(OBJS) $(CFLAGS) $(LIB_MAC) libft/libft.a -o $(NAME)
endif


clean:
	@make clean -C ./libft
	${RM} ${OBJS} 

fclean: clean
	@make fclean -C ./libft
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
