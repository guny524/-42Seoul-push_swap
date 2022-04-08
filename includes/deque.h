/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:22:18 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/08 21:54:46 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEQUE_H
# define DEQUE_H

# include <stddef.h>
# include "push_swap.h"
/*
* check forward declaration in push_swap.h
*/
typedef int			t_deque_data;

typedef struct s_deuqe_node
{
	t_deque_data		data;
	struct s_deuqe_node	*next;
	struct s_deuqe_node	*before;
}	t_deque_node;

typedef struct s_deque
{
	t_deque_node	head;
	t_deque_node	tail;
	size_t			size;
}	t_deque;

typedef enum e_deque
{
	DEQUE_HEAD,
	DEQUE_TAIL,
	DEQUE_A,
	DEQUE_B,
}	t_e_deque;

typedef struct s_ps	t_ps;

/*
* deque.c
*/
t_deque_node	*new_deque_node(t_deque_data data, t_ps *ps);
t_deque			*new_deque(t_ps *ps, t_e_deque which);
void			deque_push(t_deque *d, t_deque_data data, t_e_deque where,
					t_ps *ps);
t_deque_data	deque_pop(t_deque *d, t_e_deque where, t_ps *ps);
void			free_deque(t_deque *d);

#endif
