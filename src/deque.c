/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:45:37 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/08 20:25:39 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "push_swap.h"
#include "error.h"

#include "debug.h"

/*
* Malloc new node for deque and return it.
*
* @praram[in] data for node data.
* @praram[out] ps is necessary to free malloced deque and other arrays in ps.
*/
t_deque_node	*new_deque_node(t_deque_data data, t_ps *ps)
{
	t_deque_node	*n;

	n = malloc(sizeof(t_deque_node));
	if (NULL == n)
		free_ps_error_print_exit(ps, "node malloc fail\n");
	n->data = data;
	return (n);
}

/*
* Malloc new deque and set a or b in ps point to it and return it.
*
* @praram[out] ps is necessary to free malloced deque and other arrays in ps,
* and access to a, b deque.
* @praram[in] which indicate which deque to point to malloced deque.
* DEQUE_A or DEQUE_B.
*/
t_deque	*new_deque(t_ps *ps, t_e_deque which)
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
	if (DEQUE_A == which)
		ps->a = d;
	else if (DEQUE_B == which)
		ps->b = d;
	else
		free_ps_error_print_exit(ps, "none a or b ether\n");
	return (d);
}

/*
* Push data in deque.
*
* @praram[out] d is the deque which node will be pushed into.
* @praram[in] data is the value that node will contain.
* @praram[in] where to push node in deque. DEQUE_HEAD or DEQUE_TAIL.
* @praram[out] ps is necessary to free malloced deque and other arrays in ps.
*/
void	deque_push(t_deque *d, t_deque_data data, t_e_deque where, t_ps *ps)
{
	t_deque_node	*node;

	node = new_deque_node(data, ps);
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
* Pop data in deque and return it.
* !!Always!! should check if d->size is 0 before pop.
*
* @praram[out] d is the deque which node will be poped out.
* @praram[in] where from node poped out. DEQUE_HEAD or DEQUE_TAIL.
* @praram[out] ps is necessary to free malloced deque and other arrays in ps.
*/
t_deque_data	deque_pop(t_deque *d, t_e_deque where, t_ps *ps)
{
	t_deque_node	*n;
	t_deque_data	ret;

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

/*
* Free all deque's nodes.
*
* @praram[out] d is the deque will be freed.
*/
void	free_deque(t_deque *d)
{
	t_deque_node	*n;
	t_deque_node	*tmp;

	n = d->head.next;
	while (n != &d->tail)
	{
		tmp = n;
		n = n->next;
		free(tmp);
	}
	free(d);
}

#ifdef DEBUG
void	deque_print(t_deque *d)
{
	t_deque_node	*n = d->head.next;
	int				cnt = 0;

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
#endif
