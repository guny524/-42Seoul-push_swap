/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:09:18 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/07 09:11:14 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stddef.h>
# include "deque.h"

/*
* check forward declaration in deque.h
*/
typedef int				t_deque_data;

typedef struct s_deque	t_deque;

typedef struct s_ps
{
	t_deque			*a;
	t_deque			*b;
	t_deque_data	*arr;
	t_deque_data	*dp;
	t_deque_data	*lis;
	size_t			lis_size;
}	t_ps;

/*
* main.c
*/
t_ps	init_ps(void);
void	optimize_small_than_five(t_ps *ps);

#endif
