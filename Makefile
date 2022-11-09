NAME	= sudoku

SRCS	= sudoku.c

OBJS	= $(SRCS:.c=.o)

CC		= clang

CFLAGS	= -Wall -Wextra -Werror

RM		= rm -rf

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

%.o : %.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJS)

fclean :	clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
