/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:30:25 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/04 15:35:05 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <stddef.h>
# include "push_swap.h"

/*
* error.c
*/
size_t	ft_strlen(const char *str);
void	error_print_exit(const char *err_str);
void	free_ps(t_ps *ps);
void	free_ps_error_print_exit(t_ps *ps, const char *err_str);

#endif
