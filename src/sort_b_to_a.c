/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_b_to_a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:46:30 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/04 16:03:17 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "push_swap.h"
#include "deque.h"
#include "sort.h"

#include "debug.h"

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
	//# data가 a에 있는 값보다 젤 크거나, 작을 때 여기까지 진행
	find_max(d, r, rr);
	#ifdef DEBUG
		printf("find max in find insert\n");
		printf("ra : %ld, rra : %ld\n", *r, *rr);
	#endif
	*r += 1;
	*rr -= 1;
	#ifdef DEBUG
		printf("ra : %ld, rra : %ld\n", *r, *rr);
	#endif
}

void	run_low_cost(t_ps *ps)
{
	t_node		*n;
	t_rotate	ro;
	t_rotate	min;
	t_rotate	tmp;

	n = ps->b->head.next;
	ro = (t_rotate){0, 0, 0, ps->b->size, 0, 0};
	if (1 == ps->b->size)
		ro.rrb = 0;
	find_insert(ps->a, n->data, &ro.ra, &ro.rra);
	min = update_fourway_min(ro);
	while (n != &ps->b->tail)
	{
		find_insert(ps->a, n->data, &ro.ra, &ro.rra);
		#ifdef DEBUG
			printf("find low cost value : %d\n", n->data);
			printf("find low cost ra : %ld, rra : %ld\n", ro.ra, ro.rra);
			printf("find low cost rb : %ld, rrb : %ld\n", ro.rb, ro.rrb);
		#endif
		tmp = update_fourway_min(ro);
		#ifdef DEBUG
			printf("update tmp ra : %ld, rra : %ld\n", tmp.ra, tmp.rra);
			printf("update tmp rb : %ld, rrb : %ld\n", tmp.rb, tmp.rrb);
			printf("update tmp rr : %ld, rrr : %ld\n", tmp.rr, tmp.rrr);
		#endif
		if (min.ra + min.rb + min.rra + min.rrb + min.rr + min.rrr
			> tmp.ra + tmp.rb + tmp.rra + tmp.rrb + tmp.rr + tmp.rrr)
			min = tmp;
		#ifdef DEBUG
			printf("min ra : %ld, rra : %ld\n", min.ra, min.rra);
			printf("min rb : %ld, rrb : %ld\n", min.rb, min.rrb);
			printf("min rr : %ld, rrr : %ld\n", min.rr, min.rrr);
		#endif
		n = n->next;
		ro.rb++;
		ro.rrb--;
	}
	mul_inst_run_print(INST_RR, min.rr, ps);
	mul_inst_run_print(INST_RRR, min.rrr, ps);
	mul_inst_run_print(INST_RA, min.ra, ps);
	mul_inst_run_print(INST_RRA, min.rra, ps);
	mul_inst_run_print(INST_RB, min.rb, ps);
	mul_inst_run_print(INST_RRB, min.rrb, ps);
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
void	sort_b_to_a(t_ps *ps)
{
	size_t	ra;
	size_t	rra;

	while (ps->b->size != 0)
	{
		run_low_cost(ps);
		inst_run_print(INST_PA, ps);
	}
	find_max(ps->a, &ra, &rra);
	ra += 1;
	rra -= 1;
	if (ra <= rra)
		mul_inst_run_print(INST_RA, ra, ps);
	else
		mul_inst_run_print(INST_RRA, rra, ps);
}
