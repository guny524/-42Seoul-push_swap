# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/24 16:06:51 by min-jo            #+#    #+#              #
#    Updated: 2022/04/02 18:23:35 by min-jo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	push_swap
SRC			=	main.c deque.c error.c parse_state.c indexing.c lis.c\
				sort.c instruct.c
BDRC		=	deque.c error.c instruct.c # should add bonus
OBJ			=	$(SRC:.c=.o)
BOBJ		=	$(BSRC:.c=.o)
CFLAGS		+=	-g -fsanitize=address # -Wall -Wextra -Werror
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
