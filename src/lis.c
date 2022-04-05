/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 15:05:18 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/07 09:19:24 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "push_swap.h"
#include "error.h"

/*
* Malloc t_deque_data array as much as the size. and return it.
* If malloc failed, free all data push_swap struct have.
*
* @praram[in] size of array.
* @praram[out] ps is necessary to free malloced deque and other arrays in ps.
*/
t_deque_data	*new_data(size_t size, t_ps *ps)
{
	t_deque_data	*ret;

	ret = malloc(sizeof(t_deque_data) * size);
	if (NULL == ret)
		free_ps_error_print_exit(ps, "arr malloc fail\n");
	return (ret);
}

/*
* Malloc t_deque_data array as much size of deque A and assign it to ps->arr.
* And assign each value of deque A to arr.
*
* @praram[out] ps is necessary to free malloced deque and other arrays in ps.
* and access to ps->arr array.
*/
void	new_arr(t_ps *ps)
{
	t_deque_node	*n;
	size_t			i;

	ps->arr = new_data(ps->a->size, ps);
	i = 0;
	n = ps->a->head.next;
	while (n != &ps->a->tail)
	{
		ps->arr[i] = n->data;
		n = n->next;
		++i;
	}
}

/*
* Malloc t_deque_data array as much size of deque A and assign it to ps->dp.
* And initialize all value of dp to 1.
*
* @praram[out] ps is necessary to free malloced deque and other arrays in ps.
* and access to dynamic programming array.
*/
void	new_dp(t_ps *ps)
{
	size_t		i;

	ps->dp = new_data(ps->a->size, ps);
	i = -1;
	while (++i < ps->a->size)
		ps->dp[i] = 1;
}

/*
* Malloc t_deque_data array as much as the size of found
* longest increasing subsequence. and fill it to that value.
* Start from back of the dp array, using max_dp which is used in finding lis.
* Set to ps->lis_size size of lis array.
*
* @praram[in] max_dp is found max value of dynamic programming array.
* @praram[out] ps is necessary to free malloced deque and other arrays in ps.
* and access to lis array.
*/
void	new_lis(t_deque_data max_dp, t_ps *ps)
{
	size_t	i;

	ps->lis = new_data(max_dp, ps);
	ps->lis_size = max_dp;
	i = ps->a->size;
	while (1)
	{
		--i;
		if (max_dp == ps->dp[i])
			ps->lis[--max_dp] = ps->arr[i];
		if (0 == i)
			break ;
	}
}

/*
* Malloc dynamic programming array and arr array in ps.
* Calculate dp array. and return calculated max_dp.
* Do not free malloced array cause they used in following other func new_lis.
*
* @praram[out] ps is necessary to free malloced deque and other arrays in ps.
* and access to arr, dp array.
*/
t_deque_data	update_dp(t_ps *ps)
{
	size_t			i;
	size_t			j;
	t_deque_data	max_dp;

	new_dp(ps);
	new_arr(ps);
	max_dp = 1;
	i = 0;
	while (++i < ps->a->size)
	{
		j = -1;
		while (++j < i)
		{
			if (ps->arr[j] < ps->arr[i]
				&& ps->dp[j] + 1 > ps->dp[i])
			{
				ps->dp[i] = ps->dp[j] + 1;
				if (max_dp < ps->dp[i])
					max_dp = ps->dp[i];
			}
		}
	}
	return (max_dp);
}
