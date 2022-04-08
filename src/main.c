/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:03:34 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/08 21:56:25 by min-jo           ###   ########.fr       */
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

int	main(int argc, char *argv[])
{
	t_ps			ps;
	t_deque_data	max_dp;

	ps = init_ps();
	ps.a = new_deque(&ps, DEQUE_A);
	ps_parse_arg(argv, argc, &ps);
	if (ps.a->size <= 1)
		return (0);
	new_arr(&ps);
	quick_sort(ps.arr, 0, ps.a->size - 1);
	if (!is_unique(ps.arr, ps.a->size - 1))
		free_ps_error_print_exit(&ps, "Error\n");
	indexing(&ps);
	free(ps.arr);
	ps.arr = NULL;
	optimize_small_than_five(&ps);
	max_dp = update_dp(&ps);
	new_lis(max_dp, &ps);
	ps.b = new_deque(&ps, DEQUE_B);
	sort_a_to_b(&ps);
	sort_b_to_a(&ps);
	free_ps(&ps);
	return (0);
}
