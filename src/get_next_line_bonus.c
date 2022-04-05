/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 13:23:12 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/08 19:44:51 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line_bonus.h"

/*
** fds composed follwing structure
**
** fds
** |      NULL
** v       ^
** t_index | t_data    t_data
** (pre) --  (str)     (str)
** (fd)      (start)   (start)
** (data) -> (end)     (end)
** (cnt)     (read)    (read)
** (len)     (next) -> (next) -> NULL
** (next)
** |   ^
** v   |---
** t_index | t_data
** (pre) --  (str)
** (fd)      (start)
** (data) -> (end)
** (cnt)     (read)
** (len)     (next) -> NULL
** (next)
** |
** v
** NULL
*/

int	start(int fd, t_fds *fds, t_index **index, char **line)
{
	*index = NULL;
	if (BUFFER_SIZE == 0 || line == NULL)
		return (STATE_FD_ERROR);
	*index = find_index(fd, fds);
	if (*index == NULL)
	{
		*index = new_gnl_node(NODE_INDEX, fd);
		if (*index == NULL)
			return (STATE_MALLOC_ERROR);
		(*index)->nl_flag = 0;
		if (fds->head == NULL && fds->tail == NULL)
			fds->head = *index;
		else
		{
			fds->tail->next = *index;
			(*index)->pre = fds->tail;
		}
		fds->tail = *index;
		return (STATE_NEW_READ);
	}
	return (STATE_CHECK_NL);
}

int	check_data_nl(t_index **index, char **line)
{
	(*index)->data_tail->end = (*index)->data_tail->start;
	while ((*index)->data_tail->end < (*index)->data_tail->read)
	{
		if ((*index)->data_tail->str[(*index)->data_tail->end] == '\n')
		{
			(*index)->nl_flag = 1;
			break ;
		}
		(*index)->data_tail->end++;
	}
	(*index)->len += (*index)->data_tail->end - (*index)->data_tail->start;
	if ((*index)->nl_flag || (*index)->data_tail->read == 0)
	{
		*line = malloc(sizeof(char) * ((*index)->len) + 1);
		if (*line == NULL)
			return (STATE_MALLOC_ERROR);
		return (STATE_TIDY);
	}
	return (STATE_NEW_READ);
}

int	new_read(t_index **index)
{
	t_data	*new_data;

	new_data = new_gnl_node(NODE_DATA, NOT_USE);
	if (new_data == NULL)
		return (STATE_MALLOC_ERROR);
	new_data->read = read((*index)->fd, new_data->str, BUFFER_SIZE);
	if ((*index)->cnt == 0)
		(*index)->data_head = new_data;
	else
		(*index)->data_tail->next = new_data;
	(*index)->data_tail = new_data;
	(*index)->cnt++;
	if (new_data->read == -1)
		return (STATE_FD_ERROR);
	return (STATE_CHECK_NL);
}

int	tidy_str(t_fds *fds, t_index **index, char *line)
{
	t_data	*tmp;

	line[(*index)->len] = '\0';
	while ((*index)->cnt)
	{
		tmp = (*index)->data_head;
		ft_memcpy(line, tmp->str + tmp->start, tmp->end - tmp->start);
		line += tmp->end - tmp->start;
		if ((*index)->data_head == (*index)->data_tail)
			break ;
		(*index)->data_head = tmp->next;
		free(tmp);
		(*index)->cnt--;
	}
	(*index)->data_head->start = (*index)->data_head->end + 1;
	if ((*index)->nl_flag)
	{
		(*index)->nl_flag = 0;
		(*index)->len = 0;
		return (1);
	}
	return (free_last(fds, index, 0));
}

int	get_next_line(int fd, char **line)
{
	static t_fds	fds;
	t_state			state;
	t_index			*index;

	state = STATE_START;
	while (1)
	{
		if (state == STATE_MALLOC_ERROR)
			return (clear_fds(&fds));
		else if (state == STATE_FD_ERROR)
			return (free_last(&fds, &index, 1));
		else if (state == STATE_START)
			state = start(fd, &fds, &index, line);
		else if (state == STATE_CHECK_NL)
			state = check_data_nl(&index, line);
		else if (state == STATE_NEW_READ)
			state = new_read(&index);
		else if (state == STATE_TIDY)
			return (tidy_str(&fds, &index, *line));
	}
	return (-1);
}
