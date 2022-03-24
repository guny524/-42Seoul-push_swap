/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dequeue.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:45:37 by min-jo            #+#    #+#             */
/*   Updated: 2022/03/25 01:44:26 by min-jo           ###   ########.fr       */
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
	{
		deque_free(free_d);
		if (-1 == write(STDERR_FILENO, "node malloc fail\n", 17))
			exit(EX_IOERR);
		exit(EXIT_FAILURE);
	}
	return (n);
}

t_deque	*new_deque(void)
{
	t_deque	*d;

	d = malloc(sizeof(t_deque));
	if (NULL == d)
	{
		if (-1 == write(STDERR_FILENO, "deque malloc fail\n", 18))
			exit(EX_IOERR);
		exit(EXIT_FAILURE);
	}
	d->head = new_node(DUMMY_NODE_DATA, &d);
	d->tail = new_node(DUMMY_NODE_DATA, &d);
	d->head->before = NULL;
	d->head->next = d->tail;
	d->tail->before = d->head;
	d->tail->next = NULL;
	d->size = 0;
}

void	deque_push(t_deque *d, t_node_data data, t_e_deque where)
{
	t_node	*n;

	if (!d)
	{
		if (-1 == write(STDERR_FILENO, "deque pointer NULL but push\n", 28))
			exit(EX_IOERR);
		exit(EXIT_FAILURE);
	}
	n = new_node(data, d);
	if (E_DEQUE_HEAD == where)
	{
		n->before = d->head;
		n->next = d->head->next;
		d->head->next->before = n;
		d->head->next = n;
	}
	else if (E_DEQUE_TAIL == where)
	{
		n->before = d->tail->before;
		n->next = d->tail;
		d->tail->before->next = n;
		d->tail->before = n;
	}
}

/*
* 항상 pop 하기 전에 0 == d->size 인지 체크해야 함
*/
t_node_data	deque_pop(t_deque *d, t_e_deque where)
{
	t_node		*n;
	t_node_data	ret;

	if (!d)
	{
		if (-1 == write(STDERR_FILENO, "deque pointer NULL but pop\n", 27))
			exit(EX_IOERR);
		exit(EXIT_FAILURE);
	}
	if (E_DEQUE_HEAD == where)
	{
		n = d->head->next;
		d->head->next = n->next;
		n->next->before = d->head;
	}
	else if (E_DEQUE_TAIL == where)
	{
		n = d->tail->before;
		d->tail->before = n->before;
		n->before->next = d->tail;
	}
	ret = n->data;
	free(n);
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
	n = d->head;
	while (n)
	{
		tmp = n->next;
		free(n);
		n = tmp;
	}
	free(d);
}
