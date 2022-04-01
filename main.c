/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:07:49 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/02 18:25:04 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#include <stdio.h> //#

int	main(int argc, char *argv[])
{
	t_deque	*a;
	t_deque	*b;
	t_frees	frees;

	frees.arr = NULL;
	frees.dp = NULL;
	frees.lis = NULL;
	frees.free_n.data = NULL;
	frees.free_n.next = NULL;
	a = new_deque(&frees);
	parse_arg(argv + 1, a, &frees);
	if (a->size == 0)
		return (0);
	new_arr(a, &frees);
	quick_sort(frees.arr, 0, a->size - 1);
	if (!is_unique(frees.arr, a->size))
		free_n_error_print_exit(&frees, "Error\n");
	indexing(a, &frees);
	b = new_deque(&frees);
	if (DEBUG) //#
		deque_print(a); //#
	lis(a, &frees);
	if (DEBUG) //#
		printf("lis : "); //#
	if (DEBUG) //#
	for (size_t i=0; i<frees.lis_size; ++i) //#
		printf("%d ", frees.lis[i]); //#
	if (DEBUG) //#
		printf("\n"); //#
	a_to_b(a, b, &frees);
	b_to_a(a, b, &frees);
	if (DEBUG) //#
		deque_print(a); //#
	if (DEBUG) //#
		deque_print(b); //#
	frees_free(&frees);
	argc = 1; //#
	return (0);
}
