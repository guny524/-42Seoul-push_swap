/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:07:49 by min-jo            #+#    #+#             */
/*   Updated: 2022/03/27 18:57:45 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "push_swap.h"

int	main(int argc, char *argv[])
{
	t_deque		*a;
	t_deque		*b;
	t_free_node	free_n;

	free_n.data = NULL;
	free_n.next = NULL;
	a = new_deque(&free_n);
	parse_arg(argv + 1, a, &free_n);
	check_dup_exit(a, &free_n);
	b = new_deque(&free_n);
	// deque_print(a); //#
	// deque_print(b); //#
	sort_push_swap(a, b, &free_n);
	deque_print(a); //#
	deque_print(b); //#
	free_node_free(&free_n);
	argc = 1; //#
	return (EXIT_SUCCESS);
}
