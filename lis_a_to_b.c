/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis_a_to_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:46:07 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/03 19:01:50 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
* Check if data is in lis
*
* @praram[in] data the value to check
* @praram[in] frees necessary to use the found lis value.
*/
int	is_in_lis(t_data data, t_ps *ps)
{
	size_t	i;

	i = -1;
	while (++i < ps->lis_size)
		if (data == ps->lis[i])
			return (1);
	return (0);
}

/*
* Find the none lis value in deque d,
* and calculate the number of r and rr for that value to rise to the top.
*
* @param[in] d deque to be searched.
* @param[out] r cnt for the none lis value in deque d to go to the top.
* @param[out] rr cnt for the none lis value number in deque d to go to the top.
* @param[in] frees necessary to use the found lis value.
*/
void	find_not_lis(size_t *r, size_t *rr, t_ps *ps)
{
	t_node	*n;
	size_t	cnt;

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

void	pull_up(t_e_deque which, size_t r, size_t rr, t_ps *ps)
{
	if (r <= rr)
		while (r)
		{
			if (DEQUE_A == which)
				inst_run_print(INST_RA, ps);
			else if (DEQUE_B == which)
				inst_run_print(INST_RB, ps);
			--r;
		}
	else
		while (rr)
		{
			if (DEQUE_A == which)
				inst_run_print(INST_RRA, ps);
			else if (DEQUE_B == which)
				inst_run_print(INST_RRB, ps);
			--rr;
		}
}

/*
* @param[in] a The deque a.
* @param[in] b The deque b.
* @param[in] frees necessary to use the found lis value
* and to free the malloced deques, and lis.
*/
#include <stdio.h> //#
void	lis_a_to_b(t_ps *ps)
{
	size_t		ra;
	size_t		rra;

	while (ps->a->size != ps->lis_size)
	{
		find_not_lis(&ra, &rra, ps);
		if (DEBUG) //#
			printf("ra : %ld, rra : %ld\n", ra, rra); //#
		pull_up(DEQUE_A, ra, rra, ps);
		inst_run_print(INST_PB, ps);
	}
}
