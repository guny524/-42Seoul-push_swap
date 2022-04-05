/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:51:52 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/07 09:25:18 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "parse_state.h"
#include "error.h"

/*
* State for parsing white space. return next state.
* White space, number and sign char can be followed by after white space char.
* If encounter number and sign char, update information through num pointer.
* It is convenient to start with this state,
* since the string can have whitespace before or after it.
*
* @praram[in] s is current char to check.
* @praram[out] num is the pointer to apply the result to.
*/
t_e_state_ps_parse	state_parse_space(char s, t_ps_parse_num *num)
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

/*
* State for parsing sign. return next state.
* Only the number char can be followed by after sign char.
*
* @praram[in] s is current char to check.
* @praram[out] num is the pointer to apply the result to.
*/
t_e_state_ps_parse	state_parse_sign(char s, t_ps_parse_num *num)
{
	if ('0' <= s && s <= '9')
	{
		num->data = num->data * 10 + num->sign * (s - '0');
		return (STATE_PARSE_NUM);
	}
	else
		return (STATE_PARSE_ERROR);
}

/*
* State for parsing number. return next state.
* White space and number char can be followed by after number char.
* If encounter white space, it means the number parsing is over,
* so the number is pushed to deque A and initialized.
* Keep check the number is overflowed.
*
* @praram[in] s is current char to check.
* @praram[out] num is the pointer to apply the result to.
* @praram[out] ps is necessary to free malloced deque and other arrays in ps.
* and access to deque A.
*/
t_e_state_ps_parse	state_parse_num(char s, t_ps_parse_num *num, t_ps *ps)
{
	t_deque_data	tmp;

	if ('\t' == s || '\n' == s || '\v' == s
		|| '\f' == s || '\r' == s || ' ' == s)
	{
		deque_push(ps->a, num->data, DEQUE_TAIL, ps);
		*num = (t_ps_parse_num){1, 0};
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

/*
* Check the finished state.
* Should check last state is reasonable,
* cause while loop in parse_arg function check Null char,
* it can finish do nothing.
* It is not reasonable, if not finished with STATE_PARSE_SPACE.
*
* @praram[in] state is finished state.
* @praram[in] num is the information steel updated.
* @praram[out] ps is necessary to free malloced deque and other arrays in ps.
* and access to deque A.
*/
void	check_finish(t_e_state_ps_parse state, t_deque_data num, t_ps *ps)
{
	if (STATE_PARSE_ERROR == state || STATE_PARSE_SIGN == state)
		free_ps_error_print_exit(ps, "Error\n");
	else if (STATE_PARSE_NUM == state)
		deque_push(ps->a, num, DEQUE_TAIL, ps);
}

/*
* Parse number using state machine mechanism
* and push it to deque A from arguments string.
* Able to deal with to that situation. ./push_swap 1 2 "3 4"
*
* @praram[in] argv is array of arguments string pointer.
* @praram[in] argc is count of argv array.
* @praram[out] ps is necessary to free malloced deque and other arrays in ps.
* and access to deque A.
*/
void	ps_parse_arg(char *argv[], int argc, t_ps *ps)
{
	int					cnt;
	char				*str;
	t_e_state_ps_parse	state;
	t_ps_parse_num		num;

	cnt = 0;
	while (++cnt < argc)
	{
		str = argv[cnt];
		num = (t_ps_parse_num){1, 0};
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
