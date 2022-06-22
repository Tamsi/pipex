# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tamsibesson <tamsibesson@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/13 19:29:13 by tbesson           #+#    #+#              #
#    Updated: 2022/06/22 12:39:57 by tamsibesson      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main.c utils.c
OBJS	= ${SRCS:.c=.o}

NAME	= pipex

CC		= gcc
RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror

.c.o:
		${CC} ${CFLAGS} -c $< -o $@

${NAME}:	${OBJS}
		make -C libft
		${CC}	${CFLAGS} -o ${NAME} ${OBJS} libft/libft.a

all:		${NAME}

clean:
			make clean -C libft
			${RM} ${OBJS} ${BONUS_OBJS}

fclean:		clean
			make fclean -C libft
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
