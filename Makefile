# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/24 16:06:51 by min-jo            #+#    #+#              #
#    Updated: 2022/04/04 16:28:33 by min-jo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	push_swap

SRC_DIR		=	src/
SRC_ORI		=	push_swap.c deque.c error.c parse_state.c indexing.c lis.c\
				instruct.c sort_a_to_b.c sort_b_to_a.c sort_min.c
BSRC_ORI	=	push_swap_bonus.c

SRC			=	$(addprefix $(SRC_DIR), $(SRC_ORI))
BSRC		=	$(addprefix $(SRC_DIR), $(BSRC_ORI))

HD_DIR		=	includes/

OBJ			=	$(SRC:.c=.o)
BOBJ		=	$(BSRC:.c=.o)
CFLAGS		+=	-Wall -Wextra -Werror
CPPFLAGS	+=	-I $(HD_DIR)

all:		$(NAME)

%.o:		%.c $(addprefix $(HD_DIR), $(%.h))
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -c -o $@

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

