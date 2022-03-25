/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:13:02 by min-jo            #+#    #+#             */
/*   Updated: 2022/03/25 19:36:44 by min-jo           ###   ########.fr       */
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

void	free_d_error_print_exit(t_deque *d, const char *err_str)
{
	if (d)
		deque_free(d);
	error_print_exit(err_str);
}
