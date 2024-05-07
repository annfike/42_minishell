NAME = libft.a

SRCFILES = \
ft_itoa.c         ft_putstr_fd.c    ft_strmapi.c \
ft_atoi.c         ft_memchr.c       ft_split.c        ft_strncmp.c \
ft_bzero.c        ft_memcmp.c       ft_strchr.c       ft_strnstr.c \
ft_calloc.c       ft_memcpy.c       ft_strdup.c       ft_strrchr.c \
ft_isalnum.c      ft_memmove.c      ft_striteri.c     ft_strtrim.c \
ft_isalpha.c      ft_memset.c       ft_strjoin.c      ft_substr.c \
ft_isascii.c      ft_putchar_fd.c   ft_strlcat.c      ft_tolower.c \
ft_isdigit.c      ft_putendl_fd.c   ft_strlcpy.c      ft_toupper.c \
ft_isprint.c      ft_putnbr_fd.c    ft_strlen.c       get_next_line.c

SRCBONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
			ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OPTION = -c -I 
FLAGS = -Wall -Wextra -Werror
OBJFILES = ${SRCFILES:.c=.o}
OBJBONUS = ${SRCBONUS:.c=.o}

all:	$(NAME)

%.o: %.c
	@cc ${FLAGS} -c $< -o $@

$(NAME):	${OBJFILES}
	@ar -rc $(NAME) $(OBJFILES)
	@echo "LIBFT $(NAME)"

bonus:	${OBJFILES} ${OBJBONUS}
	@ar -rc $(NAME) ${OBJFILES} ${OBJBONUS}
	@echo "LIBFT BONUS $(NAME)"

clean:
	@rm -f $(OBJFILES) $(OBJBONUS)
	@echo "LIBFT clean"

fclean: clean
	@rm -f $(NAME)
	@echo "LIBFT fclean"

re: fclean all

.PHONY:     all clean fclean re
