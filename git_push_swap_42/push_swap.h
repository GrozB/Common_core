/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:14:40 by bgroz             #+#    #+#             */
/*   Updated: 2024/10/07 19:15:50 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <stdlib.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include <unistd.h>
# include <limits.h>

typedef struct s_stack
{
	int	*array;
	int	top;
	int	size;
	int	max_size;
}	t_stack;

t_stack	*stack_size(int size);
void	free_stack(t_stack *stack);
int		push(t_stack *stack, int value);
int		pop(t_stack *stack, int *value);
int		is_empty(t_stack *stack);
void	swap_top(t_stack *swap);
void	sa(t_stack *aswap);
void	sb(t_stack *bswap);
void	pa(t_stack *a, t_stack *b);
void	pb(t_stack *a, t_stack *b);
void	rotate(t_stack *stack);
void	ra(t_stack *a);
void	rb(t_stack *b);
void	rr(t_stack *a, t_stack *b);
void	reverse_rotate(t_stack *stack);
void	rra(t_stack *a);
void	rrb(t_stack *b);
void	rrr(t_stack *a, t_stack *b);
int		find_max_value(t_stack *stack);
void	copy_stack_to_array(t_stack *stack, int *arr);
void	sort_array(int *arr, int size);
void	sort_two(t_stack *a);
void	sort_three(t_stack *a);
void	sort_four(t_stack *a, t_stack *b);
void	sort_five(t_stack *a, t_stack *b);
int		find_min_value(t_stack *stack);
int		is_sorted(t_stack *a);
int		find_max_position(t_stack *b, int max_value);
void	simple_min_max_sort(t_stack *a, t_stack *b);
int		get_index_of_value(t_stack *stack, int value);
void	sort_stack_by_size(t_stack *a, t_stack *b);
int		calculate_rotations(int index, int size);
int		find_nth_smallest(t_stack *a, int n);
void	push_chunks_to_b(t_stack *a, t_stack *b, int chunk_size);
void	push_chunk(t_stack *a, t_stack *b, int limit, int i);
void	push_b_to_a(t_stack *a, t_stack *b);
void	push_remaining_to_b(t_stack *a, t_stack *b);
void	rotate_b_to_top(t_stack *b, int max_value, int max_value_pos);
void	print_error_and_exit(t_stack *a, t_stack *b);
int		is_number(char *str);
void	validate_and_push(t_stack *a, t_stack *b, int argc, char **argv);
int		has_duplicate(t_stack *stack, int value);
int		is_in_int_range(const char *str);

#endif