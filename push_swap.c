/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:07:49 by min-jo            #+#    #+#             */
/*   Updated: 2022/03/24 19:15:56 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sysexits.h>

void	exit_error(char **free_arg) //#
{
	if (-1 == write(STDERR_FILENO, "Error\n", 6))
		exit(EX_IOERR);
	if (free_arg) //#
		free(free_arg); //#
	exit(EXIT_FAILURE);
}

//# split 안 쓰고 atoi에서 주소 리턴해서
//#
//# int가 아니어도
//# int보다 커도
//# 중복 되어도 Error 출력해야 함

int	main(int argc, char *argv[])
{

	return (EXIT_SUCCESS);
}
