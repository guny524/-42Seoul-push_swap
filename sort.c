/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:11:27 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/02 18:17:37 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// /*
// * The optimal chunk value seems to be computed as sqrt(size) * 1.5
// * Calculate the root using Newton's method.
// *
// * @param[in] size The size of a
// */
// t_node_data	get_chunk(size_t size)
// {
// 	double	n;
// 	double	x;

// 	n = (double)size;
// 	x = 1;
// 	while (!(-0.000001 < x * x - n && x * x - n < 0.000001))
// 		x = x / 2 + n / (2 * x);
// 	return ((t_node_data)((x * 1.5) + 0.5));
// }

/*
* Check if data is in lis
*
* @praram[in] data the value to check
* @praram[in] frees necessary to use the found lis value.
*/
int	is_in_lis(t_node_data data, t_frees *frees)
{
	size_t	i;

	i = -1;
	while (++i < frees->lis_size)
		if (data == frees->lis[i])
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
void	find_not_lis(t_deque *d, size_t *r, size_t *rr, t_frees *frees)
{
	t_node	*n;
	size_t	cnt;

	n = d->head.next;
	cnt = 0;
	*r = 0;
	while (n != &d->tail)
	{
		if (!is_in_lis(n->data, frees))
		{
			*r = cnt;
			*rr = d->size - *r;
			return ;
		}
		n = n->next;
		++cnt;
	}
}

/*
* @param[in] a The deque a.
* @param[in] b The deque b.
* @param[in] frees necessary to use the found lis value
* and to free the malloced deques, and lis.
*/
#include <stdio.h> //#
void	a_to_b(t_deque *a, t_deque *b, t_frees *frees)
{
	size_t		ra;
	size_t		rra;

	while (a->size != frees->lis_size)
	{
		find_not_lis(a, &ra, &rra, frees);
		if (DEBUG) //#
			printf("ra : %ld, rra : %ld\n", ra, rra); //#
		if (ra <= rra) //# pull up top
			while (ra--)
				inst_run_print(INST_RA, a, b, frees);
		else
			while (rra--)
				inst_run_print(INST_RRA, a, b, frees);
		inst_run_print(INST_PB, a, b, frees);
		// if (b->size >= 2 && b->head.next->data < b->head.next->next->data)
		// 	inst_run_print(INST_SB, a, b, frees);
	}
}

/*
* Find the maximum value in deque d,
* and calculate the number of rb and rrb for that value to rise to the top.
*
* @param[in] d deque to be searched.
* @param[out] r cnt for the maximum number in deque d to go to the top.
* @param[out] rr cnt for the maximum number in deque d to go to the top.
*/
t_node_data	find_max(t_deque *d, size_t *r, size_t *rr)
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
* Find the largest value in deque b and push it to a.
* if need to do ra or rra in a while the largest value in b rises to the top,
* it is optimized to rr or rrr.
*
* @param[in] a The deque a.
* @param[in] b The deque b.
* @param[in] frees necessary to use the found lis value,
* and to free the malloced deques, and lis.
*/
void	b_to_a(t_deque *a, t_deque *b, t_frees *frees)
{
	t_sort_v	v;

	while (b->size != 0)
	{
		v.max_b = find_max(b, &v.rb, &v.rrb);
		if (DEBUG) //#
			printf("max_b : %d\n", v.max_b); //#
		if (DEBUG) //#
			printf("rb : %ld, rrb : %ld\n", v.rb, v.rrb); //#
		find_insert(a, v.max_b, &v.ra, &v.rra);
		if (DEBUG) //#
			printf("ra : %ld, rra : %ld\n", v.ra, v.rra); //#

		if (v.ra <= v.rra && v.rb <= v.rrb) //# pull up top
			while (v.ra && v.rb)
			{
				inst_run_print(INST_RR, a, b, frees);
				--v.ra;
				--v.rb;
			}
		else if (v.ra > v.rra && v.rb > v.rrb)
			while (v.rra && v.rrb)
			{
				inst_run_print(INST_RRR, a, b, frees);
				--v.rra;
				--v.rrb;
			}
		if (DEBUG) //#
			printf("after rr, rrr ra : %ld, rra : %ld\n", v.ra, v.rra); //#
		if (DEBUG) //#
			printf("after rr, rrr rb : %ld, rrb : %ld\n", v.rb, v.rrb); //#
		if (v.ra <= v.rra) //# pull up top
			while (v.ra)
			{
				inst_run_print(INST_RA, a, b, frees);
				--v.ra;
			}
		else
			while (v.rra)
			{
				inst_run_print(INST_RRA, a, b, frees);
				--v.rra;
			}
		if (v.rb <= v.rrb) //# pull up top
			while (v.rb)
			{
				inst_run_print(INST_RB, a, b, frees);
				--v.rb;
			}
		else
			while (v.rrb)
			{
				inst_run_print(INST_RRB, a, b, frees);
				--v.rrb;
			}
		inst_run_print(INST_PA, a, b, frees);
	}
	find_max(a, &v.ra, &v.rra);
	v.ra += 1;
	v.rra -= 1;
	if (v.ra <= v.rra) //# pull up top
		while (v.ra--)
			inst_run_print(INST_RA, a, b, frees);
	else
		while (v.rra--)
			inst_run_print(INST_RRA, a, b, frees);
}

void	find_insert(t_deque *d, t_node_data data, size_t *r, size_t *rr)
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
