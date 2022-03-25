# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/24 16:06:51 by min-jo            #+#    #+#              #
#    Updated: 2022/03/25 21:09:02 by min-jo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	push_swap
SRC			=	main.c dequeue.c error.c instruct.c parse_state.c
BDRC		=
OBJ			=	$(SRC:.c=.o)
BOBJ		=	$(BSRC:.c=.o)
CFLAGS		+=	-Wall -Wextra -Werror
# CPPFLAGS	=

all:		$(NAME)

# %.o:		%.c
# 	$(CC) $(CFLAGS) $(CPPFLAGS) $< -c -o $@

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

bonus:		$(BOBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $(NAME)
	touch bonus

clean:
	rm -f $(OBJ) bonus

fclean:		clean
	rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus
