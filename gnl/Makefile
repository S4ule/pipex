
SRCS	=	get_next_line.c\
			get_next_line_utils.c

OBJ		=	$(SRCS:.c=.o)

RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror

NAME	=	libget_next_line.a

.c.o:
			gcc $(CFLAGS) -I . -c $< -o $(<:.c=.o)

$(NAME):	$(OBJ)
			ar rcs $(NAME) $(OBJ)

all:		$(NAME)

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:	re fclean clean all
