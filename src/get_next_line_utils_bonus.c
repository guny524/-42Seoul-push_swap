/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 13:39:58 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/08 19:44:47 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line_bonus.h"

void	*new_gnl_node(int flag, int fd)
{
	t_index	*index;
	t_data	*data;

	if (flag == NODE_INDEX)
	{
		index = malloc(sizeof(t_index));
		if (!index)
			return (NULL);
		index->fd = fd;
		index->cnt = 0;
		index->len = 0;
		index->data_head = NULL;
		index->data_tail = NULL;
		index->next = NULL;
		index->pre = NULL;
		return (index);
	}
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data->start = 0;
	data->end = 0;
	data->read = 0;
	data->next = NULL;
	return (data);
}

t_index	*find_index(int fd, t_fds *fds)
{
	t_index	*index;

	index = fds->head;
	while (index)
	{
		if (index->fd == fd)
			return (index);
		index = index->next;
	}
	return (NULL);
}

int	clear_fds(t_fds *fds)
{
	t_index	*tmp_index;
	t_data	*tmp_data;

	while (fds->head)
	{
		while (fds->head->data_head)
		{
			tmp_data = fds->head->data_head;
			fds->head->data_head = fds->head->data_head->next;
			free(tmp_data);
		}
		tmp_index = fds->head;
		fds->head = fds->head->next;
		free(tmp_index);
	}
	fds->tail = NULL;
	return (-1);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*ret;

	ret = dst;
	if (dst == src)
		return (ret);
	while (n--)
	{
		*(unsigned char *)dst = *(unsigned char *)src;
		src++;
		dst++;
	}
	return (ret);
}

int	free_last(t_fds *fds, t_index **index, int fd_error)
{
	if (*index == NULL)
		return (-1);
	free((*index)->data_tail);
	if (*index == fds->head)
		fds->head = (*index)->next;
	else
		(*index)->pre->next = (*index)->next;
	if (*index == fds->tail)
		fds->tail = (*index)->pre;
	else
		(*index)->next->pre = (*index)->pre;
	free(*index);
	if (fd_error)
		return (-1);
	return (0);
}
