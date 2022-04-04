/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:08:54 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/04 15:51:49 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sysexits.h>
#include "push_swap.h"
#include "instruct.h"
#include "error.h"

/*
* 항상 pop 하기 전에 0 == d->size 인지 체크해야 함
*/
t_node	*inst_pop(t_deque *d, t_e_deque where, t_ps *ps)
{
	t_node		*node;

	node = NULL;
	if (DEQUE_HEAD == where)
	{
		node = d->head.next;
		d->head.next = node->next;
		node->next->before = &d->head;
	}
	else if (DEQUE_TAIL == where)
	{
		node = d->tail.before;
		d->tail.before = node->before;
		node->before->next = &d->tail;
	}
	else
		free_ps_error_print_exit(ps, "none head or tail ether\n");
	node->next = NULL;
	node->before = NULL;
	d->size--;
	return (node);
}

void	inst_push(t_deque *d, t_node *node, t_e_deque where, t_ps *ps)
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
	else
		free_ps_error_print_exit(ps, "none head or tail ether\n");
	d->size++;
}

void	inst_swap(t_deque *d, t_ps *ps)
{
	t_node	*first;
	t_node	*second;

	first = inst_pop(d, DEQUE_HEAD, ps);
	second = inst_pop(d, DEQUE_HEAD, ps);
	inst_push(d, first, DEQUE_HEAD, ps);
	inst_push(d, second, DEQUE_HEAD, ps);
}

void	inst_run(t_e_inst inst, t_ps *ps)
{
	if (INST_SA == inst || INST_SB == inst || INST_SS == inst)
	{
		if ((INST_SA == inst || INST_SS == inst) && ps->a->size >= 2)
			inst_swap(ps->a, ps);
		if ((INST_SB == inst || INST_SS == inst) && ps->b->size >= 2)
			inst_swap(ps->b, ps);
	}
	else if (INST_PA == inst && ps->b->size >= 1)
		inst_push(ps->a, inst_pop(ps->b, DEQUE_HEAD, ps), DEQUE_HEAD, ps);
	else if (INST_PB == inst && ps->a->size >= 1)
		inst_push(ps->b, inst_pop(ps->a, DEQUE_HEAD, ps), DEQUE_HEAD, ps);
	else if (INST_RA == inst || INST_RB == inst || INST_RR == inst)
	{
		if ((INST_RA == inst || INST_RR == inst) && ps->a->size >= 1)
			inst_push(ps->a, inst_pop(ps->a, DEQUE_HEAD, ps), DEQUE_TAIL, ps);
		if ((INST_RB == inst || INST_RR == inst) && ps->b->size >= 1)
			inst_push(ps->b, inst_pop(ps->b, DEQUE_HEAD, ps), DEQUE_TAIL, ps);
	}
	else if (INST_RRA == inst || INST_RRB == inst || INST_RRR == inst)
	{
		if ((INST_RRA == inst || INST_RRR == inst) && ps->a->size >= 1)
			inst_push(ps->a, inst_pop(ps->a, DEQUE_TAIL, ps), DEQUE_HEAD, ps);
		if ((INST_RRB == inst || INST_RRR == inst) && ps->b->size >= 1)
			inst_push(ps->b, inst_pop(ps->b, DEQUE_TAIL, ps), DEQUE_HEAD, ps);
	}
}

void	inst_run_print(t_e_inst inst, t_ps *ps)
{
	const char	*inst_str[] = {"sa\n", "sb\n", "ss\n", "pa\n", "pb\n",
								"ra\n", "rb\n", "rr\n", "rra\n", "rrb\n", "rrr\n"};

	if (-1 == write(STDOUT_FILENO, inst_str[inst], ft_strlen(inst_str[inst])))
	{
		free_ps(ps);
		exit(EX_IOERR);
	}
	inst_run(inst, ps);
}
