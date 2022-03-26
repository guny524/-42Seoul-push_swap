/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:08:54 by min-jo            #+#    #+#             */
/*   Updated: 2022/03/26 22:22:29 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sysexits.h>
#include "push_swap.h"

void	inst_swap(t_deque *d)
{
	t_node_data	first;
	t_node_data	second;

	first = deque_pop(d, DEQUE_HEAD);
	second = deque_pop(d, DEQUE_HEAD);
	deque_push(d, second, DEQUE_HEAD);
	deque_push(d, first, DEQUE_HEAD);
}

void	inst_run(t_inst inst, t_deque *a, t_deque *b)
{
	if (INST_SA == inst || INST_SB == inst || INST_SS == inst)
	{
		if ((INST_SA == inst || INST_SS == inst) && a->size >= 2)
			inst_swap(a);
		if ((INST_SB == inst || INST_SS == inst) && b->size >= 2)
			inst_swap(b);
	}
	else if (INST_PA == inst && b->size >= 1)
			deque_push(a, deque_pop(b, DEQUE_HEAD), DEQUE_HEAD);
	else if (INST_PB == inst && a->size >= 1)
			deque_push(b, deque_pop(a, DEQUE_HEAD), DEQUE_HEAD);
	else if (INST_RA == inst || INST_RB == inst || INST_RR == inst)
	{
		if ((INST_RA == inst || INST_RR == inst) && a->size >= 1)
			deque_push(a, deque_pop(a, DEQUE_HEAD), DEQUE_TAIL);
		if ((INST_RB == inst || INST_RR == inst) && b->size >= 1)
			deque_push(b, deque_pop(b, DEQUE_HEAD), DEQUE_TAIL);
	}
	else if (INST_RRA == inst || INST_RRB == inst || INST_RRR == inst)
	{
		if ((INST_RRA == inst || INST_RRR == inst) && a->size >= 1)
			deque_push(a, deque_pop(a, DEQUE_TAIL), DEQUE_HEAD);
		if ((INST_RRB == inst || INST_RRR == inst) && b->size >= 1)
			deque_push(b, deque_pop(b, DEQUE_TAIL), DEQUE_HEAD);
	}
}

void	inst_run_print(t_inst inst, t_deque *a, t_deque *b)
{
	char *inst_str[] = {"sa\n", "sb\n", "ss\n", "pa\n", "pa\n",
							"ra\n", "rb\n", "rr\n", "rra\n", "rrb\n", "rrr\n"};

	if (-1 == write(STDOUT_FILENO, inst_str[inst], ft_strlen(inst_str[inst])))
		exit(EX_IOERR);
	inst_run(inst, a, b);
}

void	sort_push_swap(t_deque *a, t_deque *b)
{
	inst_run_print(INST_PB, a, b);
}
