/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:13:02 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/04 15:34:44 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sysexits.h>
#include "push_swap.h"
#include "deque.h"

size_t	ft_strlen(const char *str)
{
	size_t	cnt;

	cnt = 0;
	while (*str)
	{
		str++;
		cnt++;
	}
	return (cnt);
}

void	error_print_exit(const char *err_str)
{
	if (-1 == write(STDERR_FILENO, err_str, ft_strlen(err_str)))
		exit(EX_IOERR);
	exit(EXIT_FAILURE);
}

/*
* 댕글링 포인터를 방지하기 위해서 free하고 바로 exit해야 함
* 아니면 ps를 전부 free하는게 아니고, 일부분만 free하는 다른 함수에서는
* 꼭 free하고 NULL을 넣어줘야함
*/
void	free_ps(t_ps *ps)
{
	if (ps->a)
		free_deque(ps->a);
	if (ps->b)
		free_deque(ps->b);
	if (ps->arr)
		free(ps->arr);
	if (ps->dp)
		free(ps->dp);
	if (ps->lis)
		free(ps->lis);
}

void	free_ps_error_print_exit(t_ps *ps, const char *err_str)
{
	free_ps(ps);
	error_print_exit(err_str);
}
