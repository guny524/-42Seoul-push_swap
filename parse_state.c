/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:51:52 by min-jo            #+#    #+#             */
/*   Updated: 2022/03/25 21:55:05 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_e_state_parse	state_parse_space(char s, t_state_data *data)
{
	if ('\t' == s || '\n' == s || '\v' == s
		|| '\f' == s || '\r' == s || ' ' == s)
		return (STATE_PARSE_SPACE);
	else if ('0' <= s && s <= '9')
	{
		data->num = data->num * 10 + s - '0';
		return (STATE_PARSE_NUM);
	}
	else if ('+' == s || '-' == s)
	{
		data->sign = 1;
		if ('-' == s)
			data->sign = -1;
		return (STATE_PARSE_SIGN);
	}
	else
		return (STATE_PARSE_ERROR);
}

t_e_state_parse	state_parse_sign(char s, int *num)
{
	if ('0' <= s && s <= '9')
	{
		*num = *num * 10 + s - '0';
		return (STATE_PARSE_NUM);
	}
	else
		return (STATE_PARSE_ERROR);
}
//# INT_MIN 인 경우 안 됨
//# sign num 따로 나누지 말고 걍 num에 -1 곱해야 할 듯
t_e_state_parse	state_parse_num(char s, t_state_data *data, t_deque *d)
{
	t_node_data	tmp;

	if ('\t' == s || '\n' == s || '\v' == s
		|| '\f' == s || '\r' == s || ' ' == s)
	{
		deque_push(d, data->sign * data->num, DEQUE_HEAD);
		*data = (t_state_data){1, 0};
		return (STATE_PARSE_SPACE);
	}
	else if ('0' <= s && s <= '9')
	{
		tmp = data->num * 10 + s - '0';
		if (tmp < data->num)
			return (STATE_PARSE_ERROR);
		data->num = tmp;
		return (STATE_PARSE_NUM);
	}
	else
		return (STATE_PARSE_ERROR);
}

void	check_finish(t_e_state_parse state, t_state_data *data, t_deque *d)
{
	if (STATE_PARSE_SIGN == state || STATE_PARSE_ERROR == state)
		free_d_error_print_exit(d, "Error\n");
	else if (STATE_PARSE_NUM == state)
		deque_push(d, data->sign * data->num, DEQUE_HEAD);
}

void	parse_arg(char *argv[], t_deque *d)
{
	char			*str;
	t_e_state_parse	state;
	t_state_data	data;

	while (*argv)
	{
		str = *argv++;
		data = (t_state_data){1, 0};
		state = STATE_PARSE_SPACE;
		while (*str)
		{
			if (STATE_PARSE_ERROR == state)
				free_d_error_print_exit(d, "Error\n");
			else if (STATE_PARSE_SPACE == state)
				state = state_parse_space(*str, &data);
			else if (STATE_PARSE_SIGN == state)
				state = state_parse_sign(*str, &data.num);
			else if (STATE_PARSE_NUM == state)
				state = state_parse_num(*str, &data, d);
			str++;
		}
		check_finish(state, &data, d);
	}
}
