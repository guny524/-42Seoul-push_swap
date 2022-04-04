/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:09:18 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/04 16:44:04 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

typedef struct s_ps	t_ps;

# include <stddef.h>
# include "deque.h"

typedef struct s_ps
{
	t_deque	*a;
	t_deque	*b;
	t_data	*arr;
	t_data	*dp;
	t_data	*lis;
	size_t	lis_size;
}	t_ps;

/*
* main.c
*/
t_ps	init_ps(void);
void	optimize_small_than_five(t_ps *ps);

#endif
