/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 13:26:37 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/08 19:45:40 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stddef.h>

# ifdef BUFFER_SIZE
#  if BUFFER_SIZE < 0
#   undef BUFFER_SIZE
#   define BUFFER_SIZE 0
#  endif
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef enum e_state
{
	STATE_MALLOC_ERROR = -1,
	STATE_FD_ERROR,
	STATE_START,
	STATE_CHECK_NL,
	STATE_NEW_READ,
	STATE_TIDY
}	t_state;

enum e_node
{
	NODE_INDEX,
	NODE_DATA,
};

# define NOT_USE -1

typedef struct s_fds
{
	struct s_index	*head;
	struct s_index	*tail;
}	t_fds;

typedef struct s_index
{
	int				fd;
	int				cnt;
	int				len;
	int				nl_flag;
	struct s_data	*data_head;
	struct s_data	*data_tail;
	struct s_index	*next;
	struct s_index	*pre;
}	t_index;

typedef struct s_data
{
	char			str[BUFFER_SIZE];
	int				start;
	int				end;
	int				read;
	struct s_data	*next;
}	t_data;

void	*new_gnl_node(int flag, int fd);
t_index	*find_index(int fd, t_fds *fds);
int		clear_fds(t_fds *fds);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		free_last(t_fds *fds, t_index **index, int fd_error);

int		start(int fd, t_fds *fds, t_index **index, char **line);
int		check_data_nl(t_index **index, char **line);
int		new_read(t_index **index);
int		tidy_str(t_fds *fds, t_index **index, char *line);
int		get_next_line(int fd, char **line);

#endif
