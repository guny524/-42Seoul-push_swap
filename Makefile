# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/24 16:06:51 by min-jo            #+#    #+#              #
#    Updated: 2022/04/05 20:36:17 by min-jo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	push_swap
BNAME		=	checker

SRC_DIR		=	src/
SRC_ORI		=	push_swap.c deque.c error.c parse_state.c indexing.c lis.c\
				instruct.c sort_a_to_b.c sort_b_to_a.c sort_min.c
BSRC_ORI	=

HD_DIR		=	includes/

SRCS			=	$(addprefix $(SRC_DIR), $(SRC_ORI))
BSRCS		=	$(addprefix $(SRC_DIR), $(BSRC_ORI))

OBJS			=	$(SRCS:.c=.o)
BOBJS		=	$(BSRCS:.c=.o)

CFLAGS		+=	-Wall -Wextra -Werror -MD
CPPFLAGS	+=	-I $(HD_DIR)
# LDFALGS		+=	-lm

all:		$(NAME)

%.o:		%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -c -o $@

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

bonus:		$(BOBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $(BNAME)
	touch bonus

clean:
	rm -f $(OBJS) $(BOBJS)
	rm -f $(addprefix $(SRC_DIR), *.d)
	rm -f bonus

fclean:		clean
	rm -f $(NAME) $(BNAME)

re:			fclean all

.PHONY:		all clean fclean re bonus

-include $(OBJS:.o=.d)
-include $(BOBJS:.o=.d)
