/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:11:27 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/01 17:57:39 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
* chunk seems to be sqrt(size) * 1.5
*/
t_node_data	get_chunk(size_t size)
{
	double	n;
	double	x;

	n = (double)size;
	x = 1;
	while (!(-0.000001 < x * x - n && x * x - n < 0.000001))
		x = x / 2 + n / (2 * x);
	return ((t_node_data)((x * 1.5) + 0.5));
}
#include <stdio.h> //#
void	a_to_b(t_deque *a, t_deque *b, t_frees *frees)
{
	t_sort_v	v;

	v = (t_sort_v){get_chunk(a->size), 0, 0};
	printf("chunk : %d\n", v.chunk);
	while (a->size != frees->lis_size)
	{
		if (a->head.next->data == frees->lis[v.lis_i])
		{
			inst_run_print(INST_RA, a, b, frees);
			if (++v.lis_i >= frees->lis_size)
				v.lis_i = 0;
		}
		else if (a->head.next->data <= v.inst_cnt)
			inst_run_print(INST_PB, a, b, frees);
		else if (a->head.next->data <= v.inst_cnt + v.chunk)
		{
			inst_run_print(INST_PB, a, b, frees);
			inst_run_print(INST_RB, a, b, frees);
		}
		else
			inst_run_print(INST_RA, a, b, frees);
		++v.inst_cnt;
		if (b->size >= 2 && b->head.next->data < b->head.next->next->data)
			inst_run_print(INST_SB, a, b, frees);
	}
}

void	b_to_a(t_deque *a, t_deque *b, t_frees *frees)
{

}
