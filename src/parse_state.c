/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:51:52 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/04 16:47:17 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "parse_state.h"
#include "error.h"

t_e_state_parse	state_parse_space(char s, t_parse_num *num)
{
	if ('\t' == s || '\n' == s || '\v' == s
		|| '\f' == s || '\r' == s || ' ' == s)
		return (STATE_PARSE_SPACE);
	else if ('0' <= s && s <= '9')
	{
		num->data = num->data * 10 + s - '0';
		return (STATE_PARSE_NUM);
	}
	else if ('+' == s || '-' == s)
	{
		if ('-' == s)
			num->sign = -1;
		return (STATE_PARSE_SIGN);
	}
	else
		return (STATE_PARSE_ERROR);
}

t_e_state_parse	state_parse_sign(char s, t_parse_num *num)
{
	if ('0' <= s && s <= '9')
	{
		num->data = num->data * 10 + num->sign * (s - '0');
		return (STATE_PARSE_NUM);
	}
	else
		return (STATE_PARSE_ERROR);
}

t_e_state_parse	state_parse_num(char s, t_parse_num *num, t_ps *ps)
{
	t_data	tmp;

	if ('\t' == s || '\n' == s || '\v' == s
		|| '\f' == s || '\r' == s || ' ' == s)
	{
		deque_push(ps->a, num->data, DEQUE_TAIL, ps);
		*num = (t_parse_num){1, 0};
		return (STATE_PARSE_SPACE);
	}
	else if ('0' <= s && s <= '9')
	{
		tmp = num->data * 10 + num->sign * (s - '0');
		if ((-1 == num->sign && tmp > num->data)
			|| (1 == num->sign && tmp < num->data))
			return (STATE_PARSE_ERROR);
		num->data = tmp;
		return (STATE_PARSE_NUM);
	}
	else
		return (STATE_PARSE_ERROR);
}

void	check_finish(t_e_state_parse state, t_data num, t_ps *ps)
{
	if (STATE_PARSE_ERROR == state || STATE_PARSE_SIGN == state)
		free_ps_error_print_exit(ps, "Error\n");
	else if (STATE_PARSE_NUM == state)
		deque_push(ps->a, num, DEQUE_TAIL, ps);
}

void	parse_arg(char *argv[], int argc, t_ps *ps)
{
	int				cnt;
	char			*str;
	t_e_state_parse	state;
	t_parse_num		num;

	cnt = 0;
	while (++cnt < argc)
	{
		str = argv[cnt];
		num = (t_parse_num){1, 0};
		state = STATE_PARSE_SPACE;
		while (*str)
		{
			if (STATE_PARSE_ERROR == state)
				free_ps_error_print_exit(ps, "Error\n");
			else if (STATE_PARSE_SPACE == state)
				state = state_parse_space(*str, &num);
			else if (STATE_PARSE_SIGN == state)
				state = state_parse_sign(*str, &num);
			else if (STATE_PARSE_NUM == state)
				state = state_parse_num(*str, &num, ps);
			str++;
		}
		check_finish(state, num.data, ps);
	}
}
