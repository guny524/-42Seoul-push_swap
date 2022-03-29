/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 15:05:18 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/01 15:00:16 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "push_swap.h"

t_node_data	*new_node_data(size_t size, t_frees *frees)
{
	t_node_data	*ret;
	size_t		i;

	ret = malloc(sizeof(t_node_data) * size);
	if (NULL == ret)
		free_n_error_print_exit(frees, "arr malloc fail\n");
	return (ret);
}

void	new_arr(t_deque *d, t_frees *frees)
{
	t_node		*n;
	size_t		i;

	frees->arr = new_node_data(d->size, frees);
	i = 0;
	n = d->head.next;
	while (n != &d->tail)
	{
		frees->arr[i] = n->data;
		n = n->next;
		++i;
	}
}

void	new_dp(size_t size, t_frees *frees)
{
	size_t		i;

	frees->dp = new_node_data(size, frees);
	i = -1;
	while (++i < size)
		frees->dp[i] = 1;
}

void	new_lis(t_lis_v v, t_frees *frees)
{
	frees->lis = new_node_data(v.max_dp, frees);
	frees->lis_size = v.max_dp;
	while (1)
	{
		--v.i;
		if (v.max_dp == frees->dp[v.i])
			frees->lis[--v.max_dp] = frees->arr[v.i];
		if (0 == v.i)
			break ;
	}
	free(frees->arr);
	frees->arr = NULL;
	free(frees->dp);
	frees->dp = NULL;
}

void	lis(t_deque *d, t_frees *frees)
{
	t_lis_v		v;

	new_dp(d->size, frees);
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
	new_lis(v, frees);
}
