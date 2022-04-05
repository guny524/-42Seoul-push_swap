/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 21:34:35 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/07 09:16:37 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "push_swap.h"

/*
* Seperate from left to right based on pivot.
* The smaller ones are on the left and the larger ones are on the right.
* Return index where pivot is.
* Perform O(n)
*
* @praram[out] arr to be sorted containing the values of deque A.
* @praram[in] left start index to find bigger than pivot to right.
* @praram[in] right start index to find bigger than pivot to left.
*/
size_t	partition(t_deque_data *arr, size_t left, size_t right)
{
	t_deque_data	pivot;
	size_t			low;
	size_t			high;
	t_deque_data	tmp;

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

/*
* Sort arr containing the values of deque A.
* Perform O(n) to seperate partition.
* Perform O(logn) to call it self recursive.
* So it perform O(nlogn)
*
* @praram[out] arr to be sorted containing the values of deque A.
* @praram[in] left border for quicksort.
* @praram[in] right border for quicksort.
*/
void	quick_sort(t_deque_data *arr, size_t left, size_t right)
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

/*
* Check uniquueness of element in sorted arr.
* Return 1 if unique, otherwise 0.
* Perform O(n) on sorted arr
*
* @praram[in] arr is sorted arr ontaining the values of deque A.
* @praram[in] size of arr. same as a->size - 1
*/
int	is_unique(t_deque_data *arr, size_t size)
{
	size_t	i;

	i = -1;
	while (++i < size)
		if (arr[i] >= arr[i + 1])
			return (0);
	return (1);
}

/*
* Search data in sorted arr.
* Return index where data found.
* Perform O(logn) on sorted arr call itself recursive.
*
* @praram[in] arr is sorted arr containing the values of deque a.
* @praram[in] data to search in arr.
* @praram[in] low start index doing binary search.
* @praram[in] high end index doing binary search.
*/
size_t	binary_search(t_deque_data *arr, t_deque_data data, size_t low,
			size_t high)
{
	size_t			mid;
	t_deque_data	item;

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

/*
* Renumber index of elemnt's from deque A densely using sorted arr.
* Perform O(n) to find where node n's data in sorted arr.
* Perform binary search O(logn) on sorted arr.
* So it performs O(nlogn)
*
* @praram[out] ps is necessary to free malloced deque and other arrays in ps.
* and access to deque A.
*/
void	indexing(t_ps *ps)
{
	t_deque_node	*n;
	size_t			ret;

	n = ps->a->head.next;
	while (n != &ps->a->tail)
	{
		ret = binary_search(ps->arr, n->data, 0, ps->a->size - 1);
		n->data = (t_deque_data)ret;
		n = n->next;
	}
}
