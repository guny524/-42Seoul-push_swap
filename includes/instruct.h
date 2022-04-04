/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruct.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:48:23 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/04 16:45:26 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTRUCT_H
# define INSTRUCT_H

typedef enum e_inst	t_e_inst;

# include "push_swap.h"
# include "deque.h"

typedef enum e_inst
{
	INST_SA,
	INST_SB,
	INST_SS,
	INST_PA,
	INST_PB,
	INST_RA,
	INST_RB,
	INST_RR,
	INST_RRA,
	INST_RRB,
	INST_RRR,
}	t_e_inst;

/*
* instructions.c
*/
t_node	*inst_pop(t_deque *d, t_e_deque where, t_ps *ps);
void	inst_push(t_deque *d, t_node *node, t_e_deque where, t_ps *ps);
void	inst_swap(t_deque *d, t_ps *ps);
void	inst_run(t_e_inst inst, t_ps *ps);
void	inst_run_print(t_e_inst inst, t_ps *ps);

#endif
