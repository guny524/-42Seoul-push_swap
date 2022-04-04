/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 15:05:18 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/04 15:56:25 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "push_swap.h"
#include "error.h"

t_data	*new_data(size_t size, t_ps *ps)
{
	t_data	*ret;

	ret = malloc(sizeof(t_data) * size);
	if (NULL == ret)
		free_ps_error_print_exit(ps, "arr malloc fail\n");
	return (ret);
}

void	new_arr(t_ps *ps)
{
	t_node		*n;
	size_t		i;

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

void	new_dp(t_ps *ps)
{
	size_t		i;

	ps->dp = new_data(ps->a->size, ps);
	i = -1;
	while (++i < ps->a->size)
		ps->dp[i] = 1;
}

void	new_lis(t_data max_dp, t_ps *ps)
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

t_data	update_dp(t_ps *ps)
{
	size_t	i;
	size_t	j;
	t_data	max_dp;

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
