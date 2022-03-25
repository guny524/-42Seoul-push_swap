/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dequeue.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:45:37 by min-jo            #+#    #+#             */
/*   Updated: 2022/03/25 21:33:06 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sysexits.h>
#include "push_swap.h"

t_node	*new_node(t_node_data data, t_deque *free_d)
{
	t_node	*n;

	n = malloc(sizeof(t_node));
	if (NULL == n)
		free_d_error_print_exit(free_d, "node malloc fail\n");
	n->data = data;
	return (n);
}

t_deque	*new_deque(t_deque *free_d)
{
	t_deque	*d;

	d = malloc(sizeof(t_deque));
	if (NULL == d)
		free_d_error_print_exit(free_d, "deque malloc fail\n");
	d->head.before = NULL;
	d->head.next = &d->tail;
	d->tail.before = &d->head;
	d->tail.next = NULL;
	d->size = 0;
	return (d);
}

void	deque_push(t_deque *d, t_node_data data, t_e_deque where)
{
	t_node	*n;

	if (!d)
		error_print_exit("deque pointer NULL but push\n");
	n = new_node(data, d);
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
t_node_data	deque_pop(t_deque *d, t_e_deque where)
{
	t_node		*n;
	t_node_data	ret;

	if (!d)
		error_print_exit("deque pointer NULL but pop\n");
	if (0 == d->size)
		free_d_error_print_exit(d, "deque size 0 but pop\n");
	if (DEQUE_HEAD == where)
	{
		n = d->head.next;
		d->head.next = n->next;
		n->next->before = &d->head;
	}
	n = d->tail.before;
	d->tail.before = n->before;
	n->before->next = &d->tail;
	ret = n->data;
	free(n);
	d->size--;
	return (ret);
}

/*
* 항상 free 하고 바로 exit 해야 함
* free 하고 바로 exit 하면 굳이 더블포인터 써서 댕글링 포인터 방지 안해도 됨
* 그러니까 deque_free하고 바로 exit 안 하는 경우 생기면 신경쓰자
*/
void	deque_free(t_deque *d)
{
	t_node	*n;
	t_node	*tmp;

	if (!d)
		return ;
	n = d->head.next;
	while (n && n != &d->tail)
	{
		tmp = n->next;
		free(n);
		n = tmp;
	}
	free(d);
}

// 이 함수 체크용이라 지워야 함
#include <stdio.h>
void	deque_print(t_deque *d)
{
	t_node	*n = d->head.next;
	int		cnt = 0;

	while (n && n != &d->tail)
	{
		printf("cnt %d : data %d : node %p\n", cnt, n->data, n);
		n = n->next;
		cnt++;
	}
}
