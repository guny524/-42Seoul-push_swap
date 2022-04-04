/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_b_to_a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:46:30 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/05 20:37:52 by min-jo           ###   ########.fr       */
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

/*
* Find the way how data value inserted in deque a.
* If the data is bigger than any other value in deque a,
* or the data is smallest than any other value in deque a,
* the while loop will break not returned.
* than will finds the way how biggest value in deque a to rise up to top.
*
* @param[in] a is the deque to data inserted in.
* @praram[in] data is the value in deque B will inserted in deque A.
* @param[out] r is the count of rotate the found index in deque A
* where the data will be inserted goes to the top.
* @param[out] rr is the count of rear rotate the found index in deque A
* where the data will be inserted goes to the top.
*/
void	find_insert(t_deque *a, t_data data, size_t *r, size_t *rr)
{
	t_node	*n;
	size_t	cnt;

	n = a->head.next;
	*r = 0;
	cnt = 0;
	while (n != &a->tail)
	{
		if ((n->before != &a->head && n->before->data < data && data < n->data)
			|| (n->before == &a->head
				&& a->tail.before->data < data && data < n->data))
		{
			*r = cnt;
			*rr = a->size - *r;
			return ;
		}
		n = n->next;
		++cnt;
	}
	find_max(a, r, rr);
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

/*
* Sum all instruction's counts to compare minimum instruction count.
*
* @praram[in] ro is the rotate instruction's counts.
*/
size_t	sum(t_rotate ro)
{
	return (ro.ra + ro.rb + ro.rra + ro.rrb + ro.rr + ro.rrr);
}

/*
* Find the low costed way to push b to a.
* if need to do ra or rra, it will be optimized to rr or rrr.
* Iterating deque B, find the index where to deque A and calculate ra, rra.
* and compare the ra, rra, rb, rrb four ways to find minimum instruction count.
*
* @praram[out] ps is necessary to free malloced deque and other arrays in ps.
* and access to deque a, b.
*/
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
		if (sum(tmp) < sum(min))
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
* Find the low costed way to push b to a. and run it.
* Cause the while condition is only check deque B's size,
* should sort rest in deque A at last.
*
* @praram[out] ps is necessary to free malloced deque and other arrays in ps.
* and access to deque a, b.
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
