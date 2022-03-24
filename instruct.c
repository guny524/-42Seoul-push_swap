/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:08:54 by min-jo            #+#    #+#             */
/*   Updated: 2022/03/24 19:45:56 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	run_instruct(t_instruct instruct)
{
	if (INSTRUCT_SA & instruct)
		instruct_swap();
	else if (INSTRUCT_PA & instruct)
		instruct_push();
	else if (INSTRUCT_RA & instruct)
		instruct_rotate();
	else if (INSTRUCT_RRA & instruct)
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
