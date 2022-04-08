/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_a_to_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:46:07 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/08 21:55:34 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "push_swap.h"
#include "instruct.h"

/*
* Check if data exist in lis array.
* Perform O(n)
*
* @param[in] data is the value to find in lis array.
* @praram[out] ps is necessary to free malloced deque and other arrays in ps.
* and access to deque A.
*/
int	is_in_lis(t_deque_data data, t_ps *ps)
{
	size_t	i;

	i = -1;
	while (++i < ps->lis_size)
		if (data == ps->lis[i])
			return (1);
	return (0);
}

/*
* Find the none lis value in deque A,
* and calculate the number of r and rr for that value to rise to the top.
*
* @param[out] r is rorate count for first found none lis value in deque A
* to go to the top.
* @param[out] rr is rear rotate count for first found none lis value in deque A
* to go to the top.
* @praram[out] ps is necessary to free malloced deque and other arrays in ps.
* and access to deque A.
*/
void	find_not_lis(size_t *r, size_t *rr, t_ps *ps)
{
	t_deque_node	*n;
	size_t			cnt;

	n = ps->a->head.next;
	cnt = 0;
	*r = 0;
	while (n != &ps->a->tail)
	{
		if (!is_in_lis(n->data, ps))
		{
			*r = cnt;
			*rr = ps->a->size - *r;
			return ;
		}
		n = n->next;
		++cnt;
	}
}

/*
* Run multiple push_swap instructions.
*
* @praram[in] inst to run
* @praram[in] cnt is the iterate number of instruction.
* @praram[out] ps is necessary to free malloced deque and other arrays in ps.
* and access to deque A.
*/
void	mul_inst_run_print(t_e_ps_inst inst, size_t cnt, t_ps *ps)
{
	size_t	i;

	i = -1;
	while (++i < cnt)
		inst_run_print(inst, ps);
}

/*
* Push b from a, which is not in found lis value.
* Find the inex where not lis value in deque A
* and compare which is fast between ra, rra.
*
* @praram[out] ps is necessary to free malloced deque and other arrays in ps.
* and access to a, b deque.
*/
void	sort_a_to_b(t_ps *ps)
{
	size_t		ra;
	size_t		rra;

	while (ps->a->size != ps->lis_size)
	{
		find_not_lis(&ra, &rra, ps);
		if (ra <= rra)
			mul_inst_run_print(PS_INST_RA, ra, ps);
		else
			mul_inst_run_print(PS_INST_RRA, rra, ps);
		inst_run_print(PS_INST_PB, ps);
	}
}
