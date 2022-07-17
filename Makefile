# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/21 23:11:14 by sbalesme          #+#    #+#              #
#    Updated: 2022/07/11 11:54:47 by sbalesme         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	srcs/main.c\
			srcs/pipex.c\
			srcs/child.c\
			srcs/child_start.c\
			srcs/pars.c\
			srcs/pars_bis.c


OBJS	=	$(SRCS:.c=.o)

HEADER	=	include

NAME	=	pipex

CC		=	gcc

CFLAG	=	-Wall -Werror -Wextra -g

.c.o:
		$(CC) $(CFLAG) -I $(HEADER) -L libft -lft -L gnl -lget_next_line -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
		make lib
		$(CC) $(CFLAG) $(OBJS) -I $(HEADER) -L libft -lft -L gnl -lget_next_line -o $(NAME)

lib:
		make -C libft all
		make -C gnl all

all:	$(NAME)

clean:
		rm -f $(OBJS)
		make -C libft clean
		make -C gnl clean

fclean:	clean
		rm -f $(NAME)
		make -C libft fclean
		make -C gnl fclean

re:		fclean
		make all

.PHONY:	re fclean clean all lib
