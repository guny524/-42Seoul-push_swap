/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:07:49 by min-jo            #+#    #+#             */
/*   Updated: 2022/03/29 21:32:34 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "push_swap.h"

int	main(int argc, char *argv[])
{
	t_deque	*a;
	t_deque	*b;
	t_frees	frees;

	frees.arr = NULL;
	frees.dp = NULL;
	frees.free_n.data = NULL;
	frees.free_n.next = NULL;
	a = new_deque(&frees);
	parse_arg(argv + 1, a, &frees);
	check_dup_exit(a, &frees);
	b = new_deque(&frees);
	deque_print(a); //#
	deque_print(b); //#
	// indexing();
	deque_print(a); //#
	deque_print(b); //#
	a_to_b(a, b, &frees);
	deque_print(a); //#
	deque_print(b); //#
	frees_free(&frees);
	argc = 1; //#
	return (EXIT_SUCCESS);
}
