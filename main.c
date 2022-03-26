/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:07:49 by min-jo            #+#    #+#             */
/*   Updated: 2022/03/26 22:22:43 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "push_swap.h"

int	main(int argc, char *argv[])
{
	t_deque	*a;
	t_deque	*b;

	a = new_deque(NULL);
	parse_arg(argv + 1, a);
	check_dup_exit(a);
	b = new_deque(a);
	// deque_print(a); //#
	// deque_print(b); //#
	sort_push_swap(a, b);
	// deque_print(a); //#
	// deque_print(b); //#
	deque_free(a);
	deque_free(b);
	argc = 1; //#
	return (EXIT_SUCCESS);
}
