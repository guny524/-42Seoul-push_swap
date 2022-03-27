/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:09:18 by min-jo            #+#    #+#             */
/*   Updated: 2022/03/29 21:32:28 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stddef.h>

typedef int	t_node_data;

typedef struct s_node
{
	t_node_data		data;
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
}	t_e_deque;

typedef	struct s_free_node
{
	struct s_deque		*data;
	struct s_free_node	*next;
}	t_free_node;

typedef struct s_frees
{
	struct s_free_node	free_n;
	t_node_data			*arr;
	t_node_data			*dp;
}	t_frees;
/*
* deque.c
*/
t_node			*new_node(t_node_data data, t_frees *frees);
t_deque			*new_deque(t_frees *frees);
void			deque_push(t_deque *d, t_node_data data, t_e_deque where,
					t_frees *frees);
t_node_data		deque_pop(t_deque *d, t_e_deque where, t_frees *frees);
void			frees_free(t_frees * frees);
// 체크용이라 지워야 함
void			deque_print(t_deque *d);
/*
* error.c
*/
size_t			ft_strlen(const char *str);
void			error_print_exit(const char *err_str);
void			free_n_error_print_exit(t_frees *frees, const char *err_str);
void			check_dup_exit(t_deque *a, t_frees *frees);
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

typedef struct s_state_data
{
	t_node_data	sign;
	t_node_data	num;
}	t_state_data;

t_e_state_parse	state_parse_space(char s, t_state_data *data);
t_e_state_parse	state_parse_sign(char s, t_state_data *data);
t_e_state_parse	state_parse_num(char s, t_state_data *data, t_deque *a,
					t_frees *frees);
void			check_finish(t_e_state_parse state, t_node_data n, t_deque *a,
					t_frees *frees);
void			parse_arg(char *argv[], t_deque *a, t_frees *frees);
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

t_node			*inst_pop(t_deque *d, t_e_deque where);
void			inst_push(t_deque *d, t_node *node, t_e_deque where);
void			inst_swap(t_deque *d);
void			inst_run(t_e_inst inst, t_deque *a, t_deque *b);
void			inst_run_print(t_e_inst inst, t_deque *a, t_deque *b,
					t_frees *frees);
/*
* sort.c
*/
void			a_to_b(t_deque *a, t_deque *b, t_frees *frees);
void			b_to_a(t_deque *a, t_deque *b, t_frees *frees);
/*
* lis.c
*/
typedef struct s_lis_v
{
	size_t		i;
	size_t		j;
	t_node_data	max_dp;
}	t_lis_v;

t_node_data		*new_dp(size_t size, t_frees *frees);
void			new_arr(t_deque *d, t_frees *frees);
t_deque			*make_lis(t_lis_v v, t_frees *frees);
t_deque			*lis_get(t_deque *d, t_frees *frees);

#endif
