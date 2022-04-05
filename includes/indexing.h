/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexing.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:43:29 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/07 09:07:56 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INDEXING_H
# define INDEXING_H

# include <stddef.h>
# include "push_swap.h"

/*
* indexing.c
*/
size_t	partition(t_deque_data *arr, size_t left, size_t right);
void	quick_sort(t_deque_data *arr, size_t left, size_t right);
int		is_unique(t_deque_data *arr, size_t size);
size_t	binary_search(t_deque_data *arr, t_deque_data data, size_t low,
			size_t high);
void	indexing(t_ps *ps);

#endif
