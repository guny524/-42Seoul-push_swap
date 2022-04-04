/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:13:02 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/04 21:13:07 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sysexits.h>
#include "push_swap.h"
#include "deque.h"

/*
* Return Null terminating string length.
*
* @praram[in] str the string will be checked it's length.
*/
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

/*
* Print error string to STDOUT and exit to fail.
* if error occur while printing error message exit with EX_IOERR.
*
* @praram[in] err_str the error string to print STDOUT
*/
void	error_print_exit(const char *err_str)
{
	if (-1 == write(STDERR_FILENO, err_str, ft_strlen(err_str)))
		exit(EX_IOERR);
	exit(EXIT_FAILURE);
}

/*
* Free all data that push_swap struct have.
* Prevent to make dangling pointer, should exit right after call this function.
* if not free all of ps have and free some part of ps,
* should assign NULL pointer to freed value that ps have
* for avoiding dangling pointer.
*
* @praram[out] ps is necessary to free malloced deque and other arrays in ps.
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

/*
* Free all data that push_swap struct have. and
* Print error string and exit.
*
* @praram[out] ps is necessary to free malloced deque and other arrays in ps.
* @praram[in] err_str the error string to print STDOUT
*/
void	free_ps_error_print_exit(t_ps *ps, const char *err_str)
{
	free_ps(ps);
	error_print_exit(err_str);
}
