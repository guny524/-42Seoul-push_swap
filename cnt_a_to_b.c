/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cnt_a_to_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:02:05 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/03 16:30:39 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
* The optimal chunk value seems to be computed as sqrt(size) * 1.5
* Calculate the root using Newton's method.
*
* @param[in] size The size of a
*/
t_data	get_chunk(size_t size)
{
	double	n;
	double	x;

	n = (double)size;
	x = 1;
	while (!(-0.000001 < x * x - n && x * x - n < 0.000001))
		x = x / 2 + n / (2 * x);
	return ((t_data)((x * 1.5) + 0.5));
}

void	cnt_a_to_b(t_ps *ps)
{
	ps = NULL; //#
}

void	cnt_b_to_a(t_ps *ps)
{
	ps = NULL; //#
}
