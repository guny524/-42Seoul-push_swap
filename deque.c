/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:45:37 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/03 18:52:10 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sysexits.h>
#include "push_swap.h"

/*
* Malloc new node for deque.
*
* @praram[in] data for node data.
* @praram[in] ps necessary to free malloced deque and other arrays in ps.
*/
t_node	*new_node(t_data data, t_ps *ps)
{
	t_node	*n;

	n = malloc(sizeof(t_node));
	if (NULL == n)
		free_ps_error_print_exit(ps, "node malloc fail\n");
	n->data = data;
	return (n);
}

/*
* Malloc new deque and set a or b in pa point to it.
*
* @praram[in] ps necessary to free malloced deque and other arrays in ps,
* and access to a, b deque.
* @praram[in] a_or_b indicate which deque to point to malloced deque.
* DEQUE_A or DEQUE_B.
*/
t_deque	*new_deque(t_ps *ps, t_e_deque a_or_b)
{
	t_deque		*d;

	d = malloc(sizeof(t_deque));
	if (NULL == d)
		free_ps_error_print_exit(ps, "deque malloc fail\n");
	d->head.before = NULL;
	d->head.next = &d->tail;
	d->tail.before = &d->head;
	d->tail.next = NULL;
	d->size = 0;
	if (DEQUE_A == a_or_b)
		ps->a = d;
	else if (DEQUE_B == a_or_b)
		ps->b = d;
	else
		free_ps_error_print_exit(ps, "none a or b ether\n");
	return (d);
}

/*
* Push data in deque.
*
* @praram[in] d the deque which node will be inserted into.
* @praram[in] data the value that node will contain.
* @praram[in] where to insert node in deque. DEQUE_HEAD or DEQUE_TAIL.
* @praram[in] ps necessary to free malloced deque and other arrays in ps.
*/
void	deque_push(t_deque *d, t_data data, t_e_deque where, t_ps *ps)
{
	t_node	*node;

	if (!d)
		free_ps_error_print_exit(ps, "deque pointer NULL but push\n");
	node = new_node(data, ps);
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
* 항상 pop 하기 전에 0 == d->size 인지 체크해야 함
*/
t_data	deque_pop(t_deque *d, t_e_deque where, t_ps *ps)
{
	t_node	*n;
	t_data	ret;

	if (!d)
		free_ps_error_print_exit(ps, "deque pointer NULL but pop\n");
	if (0 == d->size)
		free_ps_error_print_exit(ps, "deque size 0 but pop\n");
	n = NULL;
	if (DEQUE_HEAD == where)
	{
		n = d->head.next;
		d->head.next = n->next;
		n->next->before = &d->head;
	}
	else if (DEQUE_TAIL == where)
	{
		n = d->tail.before;
		d->tail.before = n->before;
		n->before->next = &d->tail;
	}
	else
		free_ps_error_print_exit(ps, "none head or tail ether\n");
	ret = n->data;
	free(n);
	d->size--;
	return (ret);
}

void	free_deque(t_deque *d)
{
	t_node	*n;
	t_node	*tmp;

	n = d->head.next;
	while (n != &d->tail)
	{
		tmp = n;
		n = n->next;
		free(tmp);
	}
	free(d);
}

// 이 함수 체크용이라 지워야 함
#include <stdio.h>
void	deque_print(t_deque *d)
{
	t_node	*n = d->head.next;
	int		cnt = 0;

	printf("d : %p\n", d);
	printf("head : %p, data : %d, before : %p, next : %p\n", &d->head, d->head.data, d->head.before, d->head.next);
	printf("tail : %p, data : %d, before : %p, next : %p\n", &d->tail, d->tail.data, d->tail.before, d->tail.next);
	while (n && n != &d->tail)
	{
		printf("cnt : %d, node : %p, data : %d, before : %p, next : %p\n", cnt, n, n->data, n->before, n->next);
		n = n->next;
		cnt++;
	}
	printf("\n");
}
