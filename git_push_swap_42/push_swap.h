/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:14:40 by bgroz             #+#    #+#             */
/*   Updated: 2024/10/01 18:55:38 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <stdlib.h>
# include "libft/libft.h"

typedef struct s_stack
{
	int	*array;
	int	top;
	int	size;
	int	max_size;
}	t_stack;

t_stack	*stack_size(int size);
void	free_stack(t_stack *stack);
int	push(t_stack *stack, int value);
int	pop(t_stack *stack, int *value);
int	is_empty(t_stack *stack);
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
void	calculate_thresholds(int *arr, int *thresholds, int size, int num_chunks);
int	find_max_value(t_stack *stack);
void push_to_b(t_stack *a, t_stack *b, int *thresholds, int num_chunks);
void	push_back_to_a(t_stack *a, t_stack *b);
void	copy_stack_to_array(t_stack *stack, int *arr);
void	sort_array(int *arr, int size);
void	sort_two(t_stack *a);
void	sort_three(t_stack *a);
void	sort_four(t_stack *a, t_stack *b);
void	sort_five(t_stack *a, t_stack *b);
void	quicksort_push_swap(t_stack *a, t_stack *b);
int find_min_value(t_stack *stack);
int	is_sorted(t_stack *a);
int	find_max_position(t_stack *b, int max_value);
void	quicksort_push_swap(t_stack *a, t_stack *b);
void	sort_large(t_stack *a, t_stack *b);
void	rotate_to_top_a(t_stack *a, int value);
void	rotate_to_top_b(t_stack *b, int value);
void	simple_min_max_sort(t_stack *a, t_stack *b);
int get_index_of_value(t_stack *stack, int value);
void	sort_stack_by_size(t_stack *a, t_stack *b);
int calculate_rotations(int index, int size);
int	find_next_min_value(t_stack *stack);
int	find_next_max_value(t_stack *stack);
int find_cheapest_number(t_stack *a, t_stack *b);
int	find_position_in_b(t_stack *b, int num);
int find_position_in_a(t_stack *a, int num);
int calculate_total_operations(int rotations_a, int rotations_b);
void radix_sort(t_stack *a);
void counting_sort(t_stack *a, int exp);
int get_max_value(t_stack *stack);
void insertion_sort(t_stack *a);
int find_median(t_stack *a);
int compare_int(const void *a, const void *b);
void quick_sort_stack(t_stack *a, t_stack *b);
void bubble_sort_rec(int *arr, int n);
void print_stack(t_stack *stack);
int calculate_position_in_a(t_stack *a, int value);
void rotate_to_position_a(t_stack *a, int position);
void push_chunk_to_b(t_stack *a, t_stack *b, int chunk_min, int chunk_max);
void	chunk_sort(t_stack *a, t_stack *b);
int find_nth_smallest(t_stack *a, int n);


#endif
