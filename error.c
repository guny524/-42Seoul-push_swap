/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:13:02 by min-jo            #+#    #+#             */
/*   Updated: 2022/03/27 18:48:06 by min-jo           ###   ########.fr       */
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

void	free_n_error_print_exit(t_free_node *free_n, const char *err_str)
{
	free_node_free(free_n);
	error_print_exit(err_str);
}

void	check_dup_exit(t_deque *d, t_free_node *free_n)
{
	t_node	*y;
	t_node	*x;

	y = d->head.next;
	while (y != &d->tail)
	{
		x = y->next;
		while (x != &d->tail)
		{
			if (y->data == x->data)
				free_n_error_print_exit(free_n, "Error\n");
			x = x->next;
		}
		y = y->next;
	}
}
