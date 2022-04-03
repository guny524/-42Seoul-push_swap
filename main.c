/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:07:49 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/03 17:03:51 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "push_swap.h"

#include <stdio.h> //#

/*
* Initailize push_swap struct and return it.
*/
t_ps	init_ps(void)
{
	t_ps	ret;

	ret.a = NULL;
	ret.b = NULL;
	ret.arr = NULL;
	ret.dp = NULL;
	ret.lis = NULL;
	ret.lis_size = 0;
	return (ret);
}

int	main(int argc, char *argv[])
{
	t_ps	ps;
	t_data	max_dp;

	ps = init_ps();
	ps.a = new_deque(&ps, DEQUE_A);
	parse_arg(argv, argc, &ps);
	if (ps.a->size == 0)
		return (0);
	if (DEBUG) //#
		deque_print(ps.a); //#
	new_arr(&ps);
	quick_sort(ps.arr, 0, ps.a->size - 1);
	if (!is_unique(ps.arr, ps.a->size))
		free_ps_error_print_exit(&ps, "Error\n");
	indexing(&ps);
	free(ps.arr);
	ps.arr = NULL;
	ps.b = new_deque(&ps, DEQUE_B);
	if (DEBUG) //#
		deque_print(ps.a); //#
	max_dp = update_dp(&ps);
	new_lis(max_dp, &ps);
	free(ps.arr);
	ps.arr = NULL;
	free(ps.dp);
	ps.dp = NULL;
	if (DEBUG) //#
		printf("lis : "); //#
	if (DEBUG) //#
	for (size_t i=0; i<ps.lis_size; ++i) //#
		printf("%d ", ps.lis[i]); //#
	if (DEBUG) //#
		printf("\n"); //#
	if (METHOD_LIS == METHOD)
	{
		lis_a_to_b(&ps);
		lis_b_to_a(&ps);
	}
	else if (METHOD_CNT == METHOD)
	{
		cnt_a_to_b(&ps);
		cnt_b_to_a(&ps);
	}
	if (DEBUG) //#
		deque_print(ps.a); //#
	if (DEBUG) //#
		deque_print(ps.b); //#
	free_ps(&ps);
	return (0);
}
