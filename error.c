/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:13:02 by min-jo            #+#    #+#             */
/*   Updated: 2022/03/29 16:06:49 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sysexits.h>
#include "push_swap.h"

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

void	free_n_error_print_exit(t_frees *frees, const char *err_str)
{
	frees_free(frees);
	error_print_exit(err_str);
}

void	check_dup_exit(t_deque *a, t_frees *frees)
{
	t_node	*y;
	t_node	*x;

	y = a->head.next;
	while (y != &a->tail)
	{
		x = y->next;
		while (x != &a->tail)
		{
			if (y->data == x->data)
				free_n_error_print_exit(frees, "Error\n");
			x = x->next;
		}
		y = y->next;
	}
}
