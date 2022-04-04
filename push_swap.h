/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:09:18 by min-jo            #+#    #+#             */
/*   Updated: 2022/04/04 14:08:15 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stddef.h>

// #define DEBUG

/*
* deque.c
*/
typedef int	t_data;

typedef struct s_node
{
	t_data			data;
	struct s_node	*next;
	struct s_node	*before;
}	t_node;

typedef struct s_deque
{
	struct s_node	head;
	struct s_node	tail;
	size_t			size;
}	t_deque;

typedef enum e_deque
{
	DEQUE_HEAD,
	DEQUE_TAIL,
	DEQUE_A,
	DEQUE_B,
}	t_e_deque;

typedef struct s_ps
{
	t_deque	*a;
	t_deque	*b;
	t_data	*arr;
	t_data	*dp;
	t_data	*lis;
	size_t	lis_size;
}	t_ps;

t_node			*new_node(t_data data, t_ps *ps);
t_deque			*new_deque(t_ps *ps, t_e_deque a_or_b);
void			deque_push(t_deque *d, t_data data, t_e_deque where, t_ps *ps);
t_data			deque_pop(t_deque *d, t_e_deque where, t_ps *ps);
void			free_deque(t_deque *d);
// 체크용이라 지워야 함
void			deque_print(t_deque *d);
/*
* main.c
*/
t_ps			init_ps(void);
void			optimize_small_than_five(t_ps *ps);
/*
* error.c
*/
size_t			ft_strlen(const char *str);
void			error_print_exit(const char *err_str);
void			free_ps(t_ps *ps);
void			free_ps_error_print_exit(t_ps *ps, const char *err_str);
/*
* parse_state.c
*/
typedef enum e_state_parse
{
	STATE_PARSE_ERROR,
	STATE_PARSE_SPACE,
	STATE_PARSE_SIGN,
	STATE_PARSE_NUM,
}	t_e_state_parse;

typedef struct s_parse_num
{
	t_data	sign;
	t_data	data;
}	t_parse_num;

t_e_state_parse	state_parse_space(char s, t_parse_num *num);
t_e_state_parse	state_parse_sign(char s, t_parse_num *num);
t_e_state_parse	state_parse_num(char s, t_parse_num *num, t_ps *ps);
void			check_finish(t_e_state_parse state, t_data num, t_ps *ps);
void			parse_arg(char *argv[], int argc, t_ps *ps);
/*
* indexing.c
*/
size_t			partition(t_data *arr, size_t left, size_t right);
void			quick_sort(t_data *arr, size_t left, size_t right);
int				is_unique(t_data *arr, size_t size);
size_t			binary_search(t_data *arr, t_data data, size_t low, size_t high);
void			indexing(t_ps *ps);
/*
* lis.c
*/
t_data			*new_data(size_t size, t_ps *ps);
void			new_arr(t_ps *ps);
void			new_dp(t_ps *ps);
void			new_lis(t_data max_dp, t_ps *ps);
t_data			update_dp(t_ps *ps);
/*
* instructions.c
*/
typedef enum e_inst
{
	INST_SA,
	INST_SB,
	INST_SS,
	INST_PA,
	INST_PB,
	INST_RA,
	INST_RB,
	INST_RR,
	INST_RRA,
	INST_RRB,
	INST_RRR,
}	t_e_inst;

t_node			*inst_pop(t_deque *d, t_e_deque where, t_ps *ps);
void			inst_push(t_deque *d, t_node *node, t_e_deque where, t_ps *ps);
void			inst_swap(t_deque *d, t_ps *ps);
void			inst_run(t_e_inst inst, t_ps *ps);
void			inst_run_print(t_e_inst inst, t_ps *ps);
/*
* sort_a_to_b.c
*/
typedef struct s_rotate
{
	size_t	ra;
	size_t	rra;
	size_t	rb;
	size_t	rrb;
	size_t	rr;
	size_t	rrr;
}	t_rotate;

int				is_in_lis(t_data data, t_ps *ps);
void			find_not_lis(size_t *r, size_t *rr, t_ps *ps);
void			mul_inst_run_print(t_e_inst inst, size_t cnt, t_ps *ps);
void			sort_a_to_b(t_ps *ps);
/*
* sort_b_to_a.c
*/
t_data			find_max(t_deque *d, size_t *r, size_t *rr);
void			find_insert(t_deque *d, t_data data, size_t *r, size_t *rr);
void			run_low_cost(t_ps *ps);
void			sort_b_to_a(t_ps *ps);
/*
* sort_min.c
*/
size_t			ft_min(size_t a, size_t b);
size_t			ft_max(size_t a, size_t b);
t_rotate		update_rr_rrr(t_rotate ro, t_e_inst inst);
t_rotate		update_fourway_min(t_rotate ro);

#endif
