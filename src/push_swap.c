/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:07:49 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/05 20:35:40 by min-jo           ###   ########.fr       */
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

/*
* Initailize push_swap struct and return it.
* a, b are deque.
* arr, dp, lis, lis_size is used in find lis value.
* arr is used in check duplication number too.
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

/*
* If largest number in edge put it last.
* When largest number in forefront or right in front last,
* do ra or rra put it last.
* As a result, optimized when the size is smaller than five.
*
* @praram[out] ps is necessary to free malloced deque and other arrays in ps.
* and access to deque A.
*/
void	optimize_small_than_five(t_ps *ps)
{
	if (ps->a->size - 1 == (size_t)ps->a->head.next->data)
		inst_run_print(INST_RA, ps);
	else if (ps->a->size - 1 == (size_t)ps->a->tail.before->before->data)
		inst_run_print(INST_RRA, ps);
	if (1 == ps->a->head.next->data - ps->a->head.next->next->data)
		inst_run_print(INST_SA, ps);
}

int	main(int argc, char *argv[])
{
	t_ps	ps;
	t_data	max_dp;

	ps = init_ps();
	ps.a = new_deque(&ps, DEQUE_A);
	parse_arg(argv, argc, &ps);
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
	ps.b = new_deque(&ps, DEQUE_B);
	max_dp = update_dp(&ps);
	new_lis(max_dp, &ps);
	free(ps.arr);
	ps.arr = NULL;
	free(ps.dp);
	ps.dp = NULL;
	#ifdef DEBUG
	printf("lis : ");
	for (size_t i=0; i<ps.lis_size; ++i)
		printf("%d ", ps.lis[i]);
	printf("\n");
	#endif
	sort_a_to_b(&ps);
	sort_b_to_a(&ps);
	#ifdef DEBUG
	deque_print(ps.a);
	deque_print(ps.b);
	#endif
	free_ps(&ps);
	return (0);
}
