/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexing.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:43:29 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/04 15:54:43 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INDEXING_H
# define INDEXING_H

# include <stddef.h>
# include "push_swap.h"

/*
* indexing.c
*/
size_t	partition(t_data *arr, size_t left, size_t right);
void	quick_sort(t_data *arr, size_t left, size_t right);
int		is_unique(t_data *arr, size_t size);
size_t	binary_search(t_data *arr, t_data data, size_t low, size_t high);
void	indexing(t_ps *ps);

#endif
