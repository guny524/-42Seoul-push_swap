/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruct.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:48:23 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/07 09:14:03 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTRUCT_H
# define INSTRUCT_H

# include "push_swap.h"
# include "deque.h"

typedef enum e_ps_inst
{
	PS_INST_SA,
	PS_INST_SB,
	PS_INST_SS,
	PS_INST_PA,
	PS_INST_PB,
	PS_INST_RA,
	PS_INST_RB,
	PS_INST_RR,
	PS_INST_RRA,
	PS_INST_RRB,
	PS_INST_RRR,
}	t_e_ps_inst;

/*
* instructions.c
*/
t_deque_node	*inst_pop(t_deque *d, t_e_deque where, t_ps *ps);
void			inst_push(t_deque *d, t_deque_node *node, t_e_deque where,
					t_ps *ps);
void			inst_swap(t_deque *d, t_ps *ps);
void			inst_run(t_e_ps_inst inst, t_ps *ps);
void			inst_run_print(t_e_ps_inst inst, t_ps *ps);

#endif
