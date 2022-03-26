/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:09:18 by min-jo            #+#    #+#             */
/*   Updated: 2022/03/26 20:46:32 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stddef.h>

/*
* deque.c
*/
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

t_node			*new_node(t_node_data data, t_deque *free_d);
t_deque			*new_deque(t_deque *d);
void			deque_push(t_deque *d, t_node_data data, t_e_deque where);
t_node_data		deque_pop(t_deque *d, t_e_deque where);
void			deque_free(t_deque *d);
// 체크용이라 지워야 함
void			deque_print(t_deque *d);
/*
* error.c
*/
size_t			ft_strlen(const char *str);
void			error_print_exit(const char *err_str);
void			free_d_error_print_exit(t_deque *d, const char *err_str);
void			check_dup_exit(t_deque *d);
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
t_e_state_parse	state_parse_num(char s, t_state_data *data, t_deque *d);
void			check_finish(t_e_state_parse state, t_node_data n, t_deque *d);
void			parse_arg(char *argv[], t_deque *d);
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
}	t_inst;

void			inst_swap(t_deque *d);
void			inst_run(t_inst inst, t_deque *a, t_deque *b);
void			inst_run_print(t_inst inst, t_deque *a, t_deque *b);
void			sort_push_swap(t_deque *a, t_deque *b);

#endif
