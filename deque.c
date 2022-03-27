/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:45:37 by min-jo            #+#    #+#             */
/*   Updated: 2022/03/27 18:54:52 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sysexits.h>
#include "push_swap.h"

t_node	*new_node(t_node_data data, t_free_node *free_n)
{
	t_node	*n;

	n = malloc(sizeof(t_node));
	if (NULL == n)
		free_n_error_print_exit(free_n, "node malloc fail\n");
	n->data = data;
	return (n);
}

t_deque	*new_deque(t_free_node *free_n)
{
	t_free_node	*fn;
	t_deque		*d;

	fn = malloc(sizeof(t_free_node));
	if (NULL == fn)
		free_n_error_print_exit(free_n, "free node malloc fail\n");
	d = malloc(sizeof(t_deque));
	if (NULL == d)
	{
		free(fn);
		free_n_error_print_exit(free_n, "deque malloc fail\n");
	}
	d->head.before = NULL;
	d->head.next = &d->tail;
	d->tail.before = &d->head;
	d->tail.next = NULL;
	d->size = 0;
	fn->data = d;
	fn->next = NULL;
	free_n->next = fn;
	return (d);
}

void	deque_push(t_deque *d, t_node_data data, t_e_deque where,
			t_free_node *free_n)
{
	t_node	*n;

	if (!d)
		free_n_error_print_exit(free_n, "deque pointer NULL but push\n");
	n = new_node(data, free_n);
	if (DEQUE_HEAD == where)
	{
		n->before = &d->head;
		n->next = d->head.next;
		d->head.next->before = n;
		d->head.next = n;
	}
	else if (DEQUE_TAIL == where)
	{
		n->before = d->tail.before;
		n->next = &d->tail;
		d->tail.before->next = n;
		d->tail.before = n;
	}
	d->size++;
}

/*
* 항상 pop 하기 전에 0 == d->size 인지 체크해야 함
*/
t_node_data	deque_pop(t_deque *d, t_e_deque where, t_free_node *free_n)
{
	t_node		*n;
	t_node_data	ret;

	if (!d)
		free_n_error_print_exit(free_n, "deque pointer NULL but pop\n");
	if (0 == d->size)
		free_n_error_print_exit(free_n, "deque size 0 but pop\n");
	if (DEQUE_HEAD == where)
	{
		n = d->head.next;
		d->head.next = n->next;
		n->next->before = &d->head;
	}
	else
	{
		n = d->tail.before;
		d->tail.before = n->before;
		n->before->next = &d->tail;
	}
	ret = n->data;
	free(n);
	d->size--;
	return (ret);
}

/*
* 항상 free 하고 바로 exit 해야 함
* free 하고 바로 exit 하면 굳이 더블포인터 써서 댕글링 포인터 방지 안해도 됨
* 그러니까 free_node_free 하고 바로 exit 안 하는 경우 생기면 신경쓰자
*/
void	free_node_free(t_free_node *free_n)
{
	t_free_node	*fn_tmp;
	t_deque		*d;
	t_node		*n;
	t_node		*n_tmp;

	if (free_n)
		free_n = free_n->next;
	while (free_n)
	{
		d = free_n->data;
		n = d->head.next;
		while (n && n != &d->tail)
		{
			n_tmp = n->next;
			free(n);
			n = n_tmp;
		}
		fn_tmp = free_n->next;
		free(free_n);
		free_n = free_n->next;
	}
}

// 이 함수 체크용이라 지워야 함
#include <stdio.h>
void	deque_print(t_deque *d)
{
	t_node	*n = d->head.next;
	int		cnt = 0;

	printf("d : %p\n", d);
	// printf("head : %p, data : %d, before : %p, next : %p\n", &d->head, d->head.data, d->head.before, d->head.next);
	// printf("tail : %p, data : %d, before : %p, next : %p\n", &d->tail, d->tail.data, d->tail.before, d->tail.next);
	while (n && n != &d->tail)
	{
		printf("cnt : %d, node : %p, data : %d, before : %p, next : %p\n", cnt, n, n->data, n->before, n->next);
		n = n->next;
		cnt++;
	}
	printf("\n");
}
