/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:08:54 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/08 21:54:58 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sysexits.h>
#include "push_swap.h"
#include "instruct.h"
#include "error.h"

/*
* Run pop instruction.
* Different from deque_pop, inst_pop doesn't free malloced node.
* Just changing the existing node's pointer to use later on inst_push.
* and return poped node's address
* !!Always!! should check if d->size is 0 before pop.
*
* @praram[out] d is the deque which node will be pushed into.
* @praram[in] where to push node in deque. DEQUE_HEAD or DEQUE_TAIL.
* @praram[out] ps is necessary to free malloced deque and other arrays in ps.
*/
t_deque_node	*inst_pop(t_deque *d, t_e_deque where, t_ps *ps)
{
	t_deque_node	*node;

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

/*
* Run push instruction.
* Different from deque_push, inst_push doesn't malloc new node.
* Just changing the existing poped out node's pointer.
*
* @praram[out] d is the deque which node will be pushed into.
* @praram[out] node is the node's address that will pushed into.
* @praram[in] where to push node in deque. DEQUE_HEAD or DEQUE_TAIL.
* @praram[out] ps is necessary to free malloced deque and other arrays in ps.
*/
void	inst_push(t_deque *d, t_deque_node *node, t_e_deque where, t_ps *ps)
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

/*
* Run swap instruction.
* Switch the two element top of the deque.
*
* @praram[out] d is the deque which node will be swaped.
* @praram[out] ps is necessary to free malloced deque and other arrays in ps.
*/
void	inst_swap(t_deque *d, t_ps *ps)
{
	t_deque_node	*first;
	t_deque_node	*second;

	first = inst_pop(d, DEQUE_HEAD, ps);
	second = inst_pop(d, DEQUE_HEAD, ps);
	inst_push(d, first, DEQUE_HEAD, ps);
	inst_push(d, second, DEQUE_HEAD, ps);
}

/*
* Just run push_swap instruction not print it.
* Even if there is no element on deque no error will be occur
*
* @praram[in] inst is instruction perform push_swap operation.
* @praram[out] ps is necessary to free malloced deque and other arrays in ps.
*/
void	inst_run(t_e_ps_inst inst, t_ps *ps)
{
	if (PS_INST_SA == inst || PS_INST_SB == inst || PS_INST_SS == inst)
	{
		if ((PS_INST_SA == inst || PS_INST_SS == inst) && ps->a->size >= 2)
			inst_swap(ps->a, ps);
		if ((PS_INST_SB == inst || PS_INST_SS == inst) && ps->b->size >= 2)
			inst_swap(ps->b, ps);
	}
	else if (PS_INST_PA == inst && ps->b->size >= 1)
		inst_push(ps->a, inst_pop(ps->b, DEQUE_HEAD, ps), DEQUE_HEAD, ps);
	else if (PS_INST_PB == inst && ps->a->size >= 1)
		inst_push(ps->b, inst_pop(ps->a, DEQUE_HEAD, ps), DEQUE_HEAD, ps);
	else if (PS_INST_RA == inst || PS_INST_RB == inst || PS_INST_RR == inst)
	{
		if ((PS_INST_RA == inst || PS_INST_RR == inst) && ps->a->size >= 1)
			inst_push(ps->a, inst_pop(ps->a, DEQUE_HEAD, ps), DEQUE_TAIL, ps);
		if ((PS_INST_RB == inst || PS_INST_RR == inst) && ps->b->size >= 1)
			inst_push(ps->b, inst_pop(ps->b, DEQUE_HEAD, ps), DEQUE_TAIL, ps);
	}
	else if (PS_INST_RRA == inst || PS_INST_RRB == inst || PS_INST_RRR == inst)
	{
		if ((PS_INST_RRA == inst || PS_INST_RRR == inst) && ps->a->size >= 1)
			inst_push(ps->a, inst_pop(ps->a, DEQUE_TAIL, ps), DEQUE_HEAD, ps);
		if ((PS_INST_RRB == inst || PS_INST_RRR == inst) && ps->b->size >= 1)
			inst_push(ps->b, inst_pop(ps->b, DEQUE_TAIL, ps), DEQUE_HEAD, ps);
	}
}

/*
* Run push_swap instruction and print it.
*
* @praram[in] inst is instruction perform push_swap operation.
* @praram[out] ps is necessary to free malloced deque and other arrays in ps.
*/
void	inst_run_print(t_e_ps_inst inst, t_ps *ps)
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
