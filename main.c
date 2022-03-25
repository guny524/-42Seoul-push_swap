/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:07:49 by min-jo            #+#    #+#             */
/*   Updated: 2022/03/25 21:54:48 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "push_swap.h"

int	main(int argc, char *argv[])
{
	t_deque	*a;
	// t_deque	*b;

	a = new_deque(NULL);
	parse_arg(argv + 1, a);
	deque_print(a);
	//# INT_MIN 인 경우 고쳐야 함
	//# 중복 체크 해야 함
	argc = 1; //#
	// b = new_deque(a);

	return (EXIT_SUCCESS);
}