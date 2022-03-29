/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 21:34:35 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/01 15:37:24 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "push_swap.h"

size_t	partition(t_node_data *arr, size_t left, size_t right)
{
	t_node_data	pivot;
	size_t		low;
	size_t		high;
	t_node_data	tmp;

	pivot = arr[left];
	low = left;
	high = right;
	while (low < high)
	{
		while (low < high && pivot <= arr[high])
			--high;
		while (low < high && pivot >= arr[low])
			++low;
		if (low < high)
		{
			tmp = arr[low];
			arr[low] = arr[high];
			arr[high] = tmp;
		}
	}
	arr[left] = arr[low];
	arr[low] = pivot;
	return (low);
}

void	quick_sort(t_node_data *arr, size_t left, size_t right)
{
	size_t	pivot_index;

	if (right <= left)
		return ;
	pivot_index = partition(arr, left, right);
	if (pivot_index - 1 < pivot_index)
		quick_sort(arr, left, pivot_index - 1);
	if (pivot_index < pivot_index + 1)
		quick_sort(arr, pivot_index + 1, right);
}

int	is_unique(t_node_data *arr, size_t size)
{
	size_t	i;

	i = -1;
	while (++i < size - 1)
		if (arr[i] >= arr[i + 1])
			return (0);
	return (1);
}

size_t	binary_search(t_node_data *arr, t_node_data data, size_t low,
			size_t high)
{
	size_t		mid;
	t_node_data	item;

	if (high < low)
		return (0);
	mid = (low + high) / 2;
	item = arr[mid];
	if (data < item && low < mid)
		return (binary_search(arr, data, low, mid - 1));
	else if (item < data && mid < high)
		return (binary_search(arr, data, mid + 1, high));
	return (mid);
}

void	indexing(t_deque *d, t_frees *frees)
{
	t_node		*n;
	size_t		ret;

	n = d->head.next;
	while (n != &d->tail)
	{
		ret = binary_search(frees->arr, n->data, 0, d->size - 1);
		n->data = (t_node_data)ret;
		n = n->next;
	}
	free(frees->arr);
	frees->arr = NULL;
}
