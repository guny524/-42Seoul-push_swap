/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:46:32 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/04 15:47:30 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIS_H
# define LIS_H

# include <stddef.h>
# include "push_swap.h"

/*
* lis.c
*/
t_data	*new_data(size_t size, t_ps *ps);
void	new_arr(t_ps *ps);
void	new_dp(t_ps *ps);
void	new_lis(t_data max_dp, t_ps *ps);
t_data	update_dp(t_ps *ps);

#endif
