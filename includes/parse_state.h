/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_state.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:36:13 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/07 09:20:36 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_STATE_H
# define PARSE_STATE_H

# include "push_swap.h"

typedef enum e_state_ps_parse
{
	STATE_PARSE_ERROR,
	STATE_PARSE_SPACE,
	STATE_PARSE_SIGN,
	STATE_PARSE_NUM,
}	t_e_state_ps_parse;

typedef struct s_ps_parse_num
{
	t_deque_data	sign;
	t_deque_data	data;
}	t_ps_parse_num;

/*
* parse_state.c
*/
t_e_state_ps_parse	state_ps_parse_space(char s, t_ps_parse_num *num);
t_e_state_ps_parse	state_ps_parse_sign(char s, t_ps_parse_num *num);
t_e_state_ps_parse	state_ps_parse_num(char s, t_ps_parse_num *num, t_ps *ps);
void				check_finish(t_e_state_ps_parse state, t_deque_data num,
						t_ps *ps);
void				ps_parse_arg(char *argv[], int argc, t_ps *ps);

#endif
