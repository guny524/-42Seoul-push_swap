/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:42:15 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/08 21:58:54 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "push_swap.h"
#include "deque.h"
#include "error.h"
#include "parse_state.h"
#include "instruct.h"
#include "get_next_line_bonus.h"
#include "sort.h"

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (*s1 && *s2 && i + 1 < n)
	{
		if (*s1 != *s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		s1++;
		s2++;
		i++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

static void	is_sorted(t_ps *ps)
{
	t_deque_node	*n;

	if (0 != ps->b->size)
		free_ps_error_print_exit(ps, "KO\n");
	n = ps->a->head.next;
	while (n->next != &ps->a->tail)
	{
		if (!(n->data < n->next->data))
			free_ps_error_print_exit(ps, "KO\n");
		n = n->next;
	}
	free_ps_error_print_exit(ps, "OK\n");
}

int	main(int argc, char *argv[])
{
	t_ps		ps;
	char		*line;
	const char	*inst_str[] = {"sa", "sb", "ss", "pa", "pb",
		"ra", "rb", "rr", "rra", "rrb", "rrr"};
	size_t		cnt;

	ps = init_ps();
	ps.a = new_deque(&ps, DEQUE_A);
	ps_parse_arg(argv, argc, &ps);
	if (ps.a->size <= 1)
		return (0);
	ps.b = new_deque(&ps, DEQUE_B);
	while (0 < get_next_line(0, &line))
	{
		cnt = 0;
		while (cnt < 11 && ft_strncmp(line, inst_str[cnt],
				ft_max(ft_strlen(line), ft_strlen(inst_str[cnt]))))
			++cnt;
		free(line);
		if (11 == cnt)
			free_ps_error_print_exit(&ps, "Error\n");
		inst_run(cnt, &ps);
	}
	is_sorted(&ps);
	return (0);
}
