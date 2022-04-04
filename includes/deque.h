/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:22:18 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/04 16:45:00 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEQUE_H
# define DEQUE_H

typedef struct s_node	t_node;
typedef struct s_deque	t_deque;
typedef enum e_deque	t_e_deque;

# include <stddef.h>
# include "push_swap.h"

typedef int	t_data;

typedef struct s_node
{
	t_data			data;
	struct s_node	*next;
	struct s_node	*before;
}	t_node;

typedef struct s_deque
{
	struct s_node	head;
	struct s_node	tail;
	size_t			size;
}	t_deque;

typedef enum e_deque
{
	DEQUE_HEAD,
	DEQUE_TAIL,
	DEQUE_A,
	DEQUE_B,
}	t_e_deque;

/*
* deque.c
*/
t_node	*new_node(t_data data, t_ps *ps);
t_deque	*new_deque(t_ps *ps, t_e_deque a_or_b);
void	deque_push(t_deque *d, t_data data, t_e_deque where, t_ps *ps);
t_data	deque_pop(t_deque *d, t_e_deque where, t_ps *ps);
void	free_deque(t_deque *d);

# include "debug.h"
#ifdef DEBUG
void	deque_print(t_deque *d);
#endif

#endif
