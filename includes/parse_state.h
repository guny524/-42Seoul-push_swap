/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_state.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:36:13 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/04 17:24:08 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_STATE_H
# define PARSE_STATE_H

# include "push_swap.h"

typedef enum e_state_parse
{
	STATE_PARSE_ERROR,
	STATE_PARSE_SPACE,
	STATE_PARSE_SIGN,
	STATE_PARSE_NUM,
}	t_e_state_parse;

typedef struct s_parse_num
{
	t_data	sign;
	t_data	data;
}	t_parse_num;

/*
* parse_state.c
*/
t_e_state_parse	state_parse_space(char s, t_parse_num *num);
t_e_state_parse	state_parse_sign(char s, t_parse_num *num);
t_e_state_parse	state_parse_num(char s, t_parse_num *num, t_ps *ps);
void			check_finish(t_e_state_parse state, t_data num, t_ps *ps);
void			parse_arg(char *argv[], int argc, t_ps *ps);

#endif
