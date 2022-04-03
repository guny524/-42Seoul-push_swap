/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis_b_to_a.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:46:30 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/03 19:15:56 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#include <stdio.h> //#

/*
* Find the maximum value in deque d,
* and calculate the number of rb and rrb for that value to rise to the top.
*
* @param[in] d deque to be searched.
* @param[out] r cnt for the maximum number in deque d to go to the top.
* @param[out] rr cnt for the maximum number in deque d to go to the top.
*/
t_data	find_max(t_deque *d, size_t *r, size_t *rr)
{
	t_node	*n;
	t_node	*max;
	size_t	cnt;

	n = d->head.next;
	max = n;
	*r = 0;
	cnt = 0;
	while (n != &d->tail)
	{
		if (max->data < n->data)
		{
			max = n;
			*r = cnt;
		}
		n = n->next;
		++cnt;
	}
	*rr = d->size - *r;
	return (max->data);
}


void	find_insert(t_deque *d, t_data data, size_t *r, size_t *rr)
{
	t_node	*n;
	size_t	cnt;

	n = d->head.next;
	*r = 0;
	cnt = 0;
	while (n != &d->tail)
	{
		if ((n->before != &d->head && n->before->data < data && data < n->data)
			|| (n->before == &d->head
			&& d->tail.before->data < data && data < n->data))
		{
			*r = cnt;
			*rr = d->size - *r;
			return ;
		}
		n = n->next;
		++cnt;
	}
	//# b에 제일 큰 값이 있을 때 여기까지 진행
	find_max(d, r, rr);
	if (DEBUG)
		printf("find max in find insert\n");
	if (DEBUG)
		printf("ra : %ld, rra : %ld\n", *r, *rr); //#
	*r += 1;
	*rr -= 1;
}

void	pull_up_together(t_rotate *ro, t_ps *ps)
{
	if (ro->ra <= ro->rra && ro->rb <= ro->rrb)
		while (ro->ra && ro->rb)
		{
			inst_run_print(INST_RR, ps);
			--ro->ra;
			--ro->rb;
		}
	else if (ro->ra > ro->rra && ro->rb > ro->rrb)
		while (ro->rra && ro->rrb)
		{
			inst_run_print(INST_RRR, ps);
			--ro->rra;
			--ro->rrb;
		}
}

/*
* Find the largest value in deque b and push it to a.
* if need to do ra or rra in a while the largest value in b rises to the top,
* it is optimized to rr or rrr.
*
* @param[in] a The deque a.
* @param[in] b The deque b.
* @param[in] frees necessary to use the found lis value,
* and to free the malloced deques, and lis.
*/
void	lis_b_to_a(t_ps *ps)
{
	t_rotate	ro;
	t_data		max_b;

	while (ps->b->size != 0)
	{
		max_b = find_max(ps->b, &ro.rb, &ro.rrb);
		if (DEBUG) //#
			printf("max_b : %d\n", max_b); //#
		if (DEBUG) //#
			printf("rb : %ld, rrb : %ld\n", ro.rb, ro.rrb); //#
		find_insert(ps->a, max_b, &ro.ra, &ro.rra);
		if (DEBUG) //#
			printf("ra : %ld, rra : %ld\n", ro.ra, ro.rra); //#
		pull_up_together(&ro, ps);
		if (DEBUG) //#
			printf("after rr, rrr ra : %ld, rra : %ld\n", ro.ra, ro.rra); //#
		if (DEBUG) //#
			printf("after rr, rrr rb : %ld, rrb : %ld\n", ro.rb, ro.rrb); //#
		pull_up(DEQUE_A, ro.ra, ro.rra, ps);
		pull_up(DEQUE_B, ro.rb, ro.rrb, ps);
		inst_run_print(INST_PA, ps);
	}
	find_max(ps->a, &ro.ra, &ro.rra);
	ro.ra += 1;
	ro.rra -= 1;
	pull_up(DEQUE_A, ro.ra, ro.rra, ps);
}
