##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## a file that make
##

RM		=	rm -f

CC		=	gcc

NAME	=	myftp

SRC		=	src/main.c	\
			src/handle_arguments.c	\
			src/print_func.c	\
			src/init_server.c	\
			src/accept_connection.c	\
			src/handle_client.c	\
			src/str_to_word_tab.c	\
			src/handle_command.c	\
			src/treat_command.c

OBJ		=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -Werror -Iinclude -g3

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean:
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
