/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:08:54 by min-jo            #+#    #+#             */
/*   Updated: 2022/03/29 16:10:04 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sysexits.h>
#include "push_swap.h"

/*
* 항상 pop 하기 전에 0 == d->size 인지 체크해야 함
*/
t_node	*inst_pop(t_deque *d, t_e_deque where)
{
	t_node		*node;

	if (DEQUE_HEAD == where)
	{
		node = d->head.next;
		d->head.next = node->next;
		node->next->before = &d->head;
	}
	else
	{
		node = d->tail.before;
		d->tail.before = node->before;
		node->before->next = &d->tail;
	}
	node->next = NULL;
	node->before = NULL;
	d->size--;
	return (node);
}

void	inst_push(t_deque *d, t_node *node, t_e_deque where)
{
	if (DEQUE_HEAD == where)
	{
		node->before = &d->head;
		node->next = d->head.next;
		d->head.next->before = node;
		d->head.next = node;
	}
	else if (DEQUE_TAIL == where)
	{
		node->before = d->tail.before;
		node->next = &d->tail;
		d->tail.before->next = node;
		d->tail.before = node;
	}
	d->size++;
}

void	inst_swap(t_deque *d)
{
	t_node	*first;
	t_node	*second;

	first = inst_pop(d, DEQUE_HEAD);
	second = inst_pop(d, DEQUE_HEAD);
	inst_push(d, second, DEQUE_HEAD);
	inst_push(d, first, DEQUE_HEAD);
}

void	inst_run(t_e_inst inst, t_deque *a, t_deque *b)
{
	if (INST_SA == inst || INST_SB == inst || INST_SS == inst)
	{
		if ((INST_SA == inst || INST_SS == inst) && a->size >= 2)
			inst_swap(a);
		if ((INST_SB == inst || INST_SS == inst) && b->size >= 2)
			inst_swap(b);
	}
	else if (INST_PA == inst && b->size >= 1)
			inst_push(a, inst_pop(b, DEQUE_HEAD), DEQUE_HEAD);
	else if (INST_PB == inst && a->size >= 1)
			inst_push(b, inst_pop(a, DEQUE_HEAD), DEQUE_HEAD);
	else if (INST_RA == inst || INST_RB == inst || INST_RR == inst)
	{
		if ((INST_RA == inst || INST_RR == inst) && a->size >= 1)
			inst_push(a, inst_pop(a, DEQUE_HEAD), DEQUE_TAIL);
		if ((INST_RB == inst || INST_RR == inst) && b->size >= 1)
			inst_push(b, inst_pop(b, DEQUE_HEAD), DEQUE_TAIL);
	}
	else if (INST_RRA == inst || INST_RRB == inst || INST_RRR == inst)
	{
		if ((INST_RRA == inst || INST_RRR == inst) && a->size >= 1)
			inst_push(a, inst_pop(a, DEQUE_TAIL), DEQUE_HEAD);
		if ((INST_RRB == inst || INST_RRR == inst) && b->size >= 1)
			inst_push(b, inst_pop(b, DEQUE_TAIL), DEQUE_HEAD);
	}
}

void	inst_run_print(t_e_inst inst, t_deque *a, t_deque *b, t_frees *frees)
{
	char *inst_str[] = {"sa\n", "sb\n", "ss\n", "pa\n", "pa\n",
							"ra\n", "rb\n", "rr\n", "rra\n", "rrb\n", "rrr\n"};

	if (-1 == write(STDOUT_FILENO, inst_str[inst], ft_strlen(inst_str[inst])))
	{
		frees_free(frees);
		exit(EX_IOERR);
	}
	inst_run(inst, a, b);
}
