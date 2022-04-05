/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:07:49 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/07 09:21:38 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "instruct.h"

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
		inst_run_print(PS_INST_RA, ps);
	else if (ps->a->size - 1 == (size_t)ps->a->tail.before->before->data)
		inst_run_print(PS_INST_RRA, ps);
	if (1 == ps->a->head.next->data - ps->a->head.next->next->data)
		inst_run_print(PS_INST_SA, ps);
}
