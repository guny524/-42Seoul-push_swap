/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_min.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:16:20 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/04 16:03:51 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stddef.h"
#include "push_swap.h"
#include "sort.h"

size_t	ft_min(size_t a, size_t b)
{
	if (a <= b)
		return (a);
	return (b);
}

size_t	ft_max(size_t a, size_t b)
{
	if (a <= b)
		return (b);
	return (a);
}

t_rotate	update_rr_rrr(t_rotate ro, t_e_inst inst)
{
	t_rotate	ret;

	ret = (t_rotate){0, 0, 0, 0, 0, 0};
	if (INST_RR == inst)
	{
		ret.rr = ft_min(ro.ra, ro.rb);
		if (ro.ra < ro.rb)
			ret.rb = ro.rb - ro.ra;
		else
			ret.ra = ro.ra - ro.rb;
	}
	else if (INST_RRR == inst)
	{
		ret.rrr = ft_min(ro.rra, ro.rrb);
		if (ro.rra < ro.rrb)
			ret.rrb = ro.rrb - ro.rra;
		else
			ret.rra = ro.rra - ro.rrb;
	}
	return (ret);
}

t_rotate	update_fourway_min(t_rotate ro)
{
	if (ft_max(ro.ra, ro.rb) <= ro.ra + ro.rrb
		&& ft_max(ro.ra, ro.rb) <= ro.rra + ro.rb
		&& ft_max(ro.ra, ro.rb) <= ft_max(ro.rra, ro.rrb))
		return (update_rr_rrr(ro, INST_RR));
	else if (ft_max(ro.rra, ro.rrb) <= ft_max(ro.ra, ro.rb)
		&& ft_max(ro.rra, ro.rrb) <= ro.ra + ro.rrb
		&& ft_max(ro.rra, ro.rrb) <= ro.rra + ro.rb)
		return (update_rr_rrr(ro, INST_RRR));
	else if (ro.ra + ro.rrb <= ft_max(ro.ra, ro.rb)
		&& ro.ra + ro.rrb <= ro.rra + ro.rb
		&& ro.ra + ro.rrb <= ft_max(ro.rra, ro.rrb))
		return ((t_rotate){ro.ra, 0, 0, ro.rrb, 0, 0});
	return ((t_rotate){0, ro.rra, ro.rb, 0, 0, 0});
}
