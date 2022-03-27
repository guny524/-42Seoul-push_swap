/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 15:05:18 by min-jo            #+#    #+#             */
/*   Updated: 2022/03/29 21:30:17 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "push_swap.h"

t_node_data	*new_dp(size_t size, t_frees *frees)
{
	t_node_data	*ret;
	size_t		i;

	ret = malloc(sizeof(t_node_data) * size);
	if (NULL == ret)
		free_n_error_print_exit(frees, "arr malloc fail\n");
	ret[0] = 1;
	i = 0;
	while (++i < size)
		ret[i] = 0;
	return (ret);
}

void	new_arr(t_deque *d, t_frees *frees)
{
	t_node		*n;
	size_t		i;

	frees->arr = new_dp(d->size, frees);
	i = 0;
	n = d->head.next;
	while (n != &d->tail)
	{
		frees->arr[i] = n->data;
		n = n->next;
		++i;
	}
}

t_deque	*make_lis(t_lis_v v, t_frees *frees)
{
	t_deque	*lis;

	lis = new_deque(frees);
	while (1)
	{
		--v.i;
		if (v.max_dp == frees->dp[v.i])
		{
			--v.max_dp;
			deque_push(lis, frees->arr[v.i], DEQUE_HEAD, frees);
		}
		if (0 == v.i)
			break ;
	}
	return (lis);
}

t_deque	*lis_get(t_deque *d, t_frees *frees)
{
	t_lis_v		v;

	frees->dp = new_dp(d->size, frees);
	new_arr(d, frees);
	v = (t_lis_v){0, -1, 1};
	while (++v.i < d->size)
	{
		v.j = -1;
		while (++v.j < v.i)
		{
			if (frees->arr[v.j] < frees->arr[v.i]
				&& frees->dp[v.j] + 1 > frees->dp[v.i])
			{
				frees->dp[v.i] = frees->dp[v.j] + 1;
				if (v.max_dp < frees->dp[v.i])
					v.max_dp = frees->dp[v.i];
			}
		}
	}
	free(frees->arr);
	free(frees->dp);
	return (make_lis(v, frees));
}
