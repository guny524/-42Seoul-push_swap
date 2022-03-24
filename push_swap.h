/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:09:18 by min-jo            #+#    #+#             */
/*   Updated: 2022/03/25 01:27:06 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP
# define PUSH_SWAP

# include <stddef.h>

/*
* push_swap.c
*/

/*
* dequeue.c
*/
# define DUMMY_NODE_DATA 0
typedef int	t_node_data;

typedef struct	s_node
{
	t_node_data	data;
	struct s_node	*next;
	struct s_node	*before;
}	t_node;

typedef struct	s_deque
{
	struct s_node	*head;
	struct s_node	*tail;
	size_t			size;
}	t_deque;

typedef enum	e_deque
{
	E_DEQUE_HEAD,
	E_DEQUE_TAIL,
}	t_e_deque;

t_node			*new_node(t_node_data data, t_deque *free_d);
t_deque			*new_deque(void);
void			deque_push(t_deque *d, t_node_data data, t_e_deque where);
t_node_data		deque_pop(t_deque *d, t_e_deque where);
void			deque_free(t_deque *d);
/*
* instructions.c
*/
typedef enum	e_instruct
{
	INSTRUCT_SA		= 0x00010,
	INSTRUCT_SB,
	INSTRUCT_SS,
	INSTRUCT_PA		= 0x00100,
	INSTRUCT_PB,
	INSTRUCT_RA		= 0x01000,
	INSTRUCT_RB,
	INSTRUCT_RR,
	INSTRUCT_RRA	= 0x10000,
	INSTRUCT_RRB,
	INSTRUCT_RRR,
}	t_instruct;

void	instruct_run(t_instruct instruct);
void	instruct_swap();
void	instruct_push();
void	instruct_rotate();
void	instruct_reverse_rotate();

#endif
