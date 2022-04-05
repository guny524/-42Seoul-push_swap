/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:03:34 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/07 09:26:42 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "push_swap.h"
#include "deque.h"
#include "parse_state.h"
#include "error.h"
#include "indexing.h"
#include "lis.h"
#include "sort.h"
#include "instruct.h"

#include "debug.h"

int	main(int argc, char *argv[])
{
	t_ps			ps;
	t_deque_data	max_dp;

	ps = init_ps();
	ps.a = new_deque(&ps, DEQUE_A);
	ps_parse_arg(argv, argc, &ps);
	if (ps.a->size <= 1)
		return (0);
	#ifdef DEBUG
	deque_print(ps.a);
	#endif
	new_arr(&ps);
	quick_sort(ps.arr, 0, ps.a->size - 1);
	if (!is_unique(ps.arr, ps.a->size - 1))
		free_ps_error_print_exit(&ps, "Error\n");
	indexing(&ps);
	free(ps.arr);
	ps.arr = NULL;
	#ifdef DEBUG
	printf("after indexing\n");
	deque_print(ps.a);
	#endif
	optimize_small_than_five(&ps);
	#ifdef DEBUG
	printf("after optimize\n");
	deque_print(ps.a);
	#endif
	max_dp = update_dp(&ps);
	new_lis(max_dp, &ps);
	free(ps.arr);
	ps.arr = NULL;
	free(ps.dp);
	ps.dp = NULL;
	#ifdef DEBUG
	printf("lis : ");
	for (size_t i = 0; i < ps.lis_size; ++i)
		printf("%d ", ps.lis[i]);
	printf("\n");
	#endif
	ps.b = new_deque(&ps, DEQUE_B);
	sort_a_to_b(&ps);
	sort_b_to_a(&ps);
	#ifdef DEBUG
	deque_print(ps.a);
	deque_print(ps.b);
	#endif
	free_ps(&ps);
	return (0);
}
