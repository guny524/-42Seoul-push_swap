/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:08:54 by min-jo            #+#    #+#             */
/*   Updated: 2022/03/26 00:53:28 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	run_instruct(t_instruct instruct)
{
	if (INSTRUCT_S_FLAG & instruct)
		instruct_swap();
	else if (INSTRUCT_P_FLAG & instruct)
		instruct_push();
	else if (INSTRUCT_R_FLAG & instruct)
		instruct_rotate();
	else if (INSTRUCT_RR_FLAG & instruct)
		instruct_reverse_rotate();
}

void	instruct_swap()
{

}

void	instruct_push()
{

}

void	instruct_rotate()
{

}

void	instruct_reverse_rotate()
{

}
