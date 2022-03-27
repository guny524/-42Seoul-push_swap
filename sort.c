/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:11:27 by min-jo            #+#    #+#             */
/*   Updated: 2022/03/29 21:32:45 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#include <stdio.h> //#

void			a_to_b(t_deque *a, t_deque *b, t_frees *frees)
{
	t_deque		*lis;
	// t_node_data	inst_cnt;

	lis = lis_get(a, frees);
	// size = a->size;
	// inst_cnt = 0;
	// while (lis->size + inst_cnt != size) //# lis 원소가 마지막이 아니면 무한 루프 돌음
	// {
	// 	printf("be lis: %ld, cnt: %d, a: %ld\n", lis->size, inst_cnt, a->size); //#
	// 	deque_pop(lis, DEQUE_HEAD, frees);
	// 	i = deque_pop(index, DEQUE_HEAD, frees);
	// 	while (i != inst_cnt)
	// 	{
	// 		inst_run_print(INST_PB, a, b, frees);
	// 		++inst_cnt;
	// 	}
	// 	inst_run_print(INST_RA, a, b, frees);
	// 	++inst_cnt;
	// 	printf("af lis: %ld, cnt: %d, a: %ld\n", lis->size, inst_cnt, a->size); //#
	// }
	// deque_print(lis); //#
	// deque_print(index); //#
}

void			b_to_a(t_deque *a, t_deque *b, t_frees *frees)
{

}
