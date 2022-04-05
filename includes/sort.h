/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:52:28 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/08 21:48:08 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORT_H
# define SORT_H

# include <stddef.h>
# include "push_swap.h"
# include "deque.h"
# include "instruct.h"

typedef struct s_rotate
{
	size_t	ra;
	size_t	rra;
	size_t	rb;
	size_t	rrb;
	size_t	rr;
	size_t	rrr;
}	t_rotate;

/*
* sort_a_to_b.c
*/
int				is_in_lis(t_deque_data data, t_ps *ps);
void			find_not_lis(size_t *r, size_t *rr, t_ps *ps);
void			mul_inst_run_print(t_e_ps_inst inst, size_t cnt, t_ps *ps);
void			sort_a_to_b(t_ps *ps);
/*
* sort_b_to_a.c
*/
t_deque_data	find_max(t_deque *d, size_t *r, size_t *rr);
void			find_insert(t_deque *a, t_deque_data data, size_t *r,
					size_t *rr);
size_t			sum(t_rotate ro);
void			run_low_cost(t_ps *ps);
void			sort_b_to_a(t_ps *ps);
/*
* sort_min.c
*/
size_t			ft_min(size_t a, size_t b);
size_t			ft_max(size_t a, size_t b);
t_rotate		update_rr_rrr(t_rotate ro, t_e_ps_inst inst);
t_rotate		update_fourway_min(t_rotate ro);
void			run_min_rotate(t_ps	*ps, t_rotate min);

#endif
