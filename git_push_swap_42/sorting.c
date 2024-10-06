/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:44:28 by bgroz            #+#    #+#             */
/*   Updated: 2024/09/13 14:44:28 by bgroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_max_value(t_stack *stack)
{
	int i;
	int max_value;

	max_value = stack->array[0];
	i = 0;
	while (i <= stack->top)
	{
		if (stack->array[i] > max_value)
			max_value = stack->array[i];
		i++;
	}
	return (max_value);
}

void copy_stack_to_array(t_stack *stack, int *arr)
{
	int i;

	i = 0;
	while (i <= stack->top)
	{
		arr[i] = stack->array[i];
		i++;
	}
}

void push_chunk(t_stack *a, t_stack *b, int limit, int i)
{
	while (i > 0)
	{
		if (a->array[0] <= limit)
			pb(a, b);
		else
			ra(a);
		i--;
	}
}

void push_chunks_to_b(t_stack *a, t_stack *b, int chunk_size)
{
	int k;
	int limit;

	k = 0;
	while (k <= 5)
	{
		limit = find_nth_smallest(a, chunk_size);
		push_chunk(a, b, limit, a->size);
		k++;
	}
}

void push_b_to_a(t_stack *a, t_stack *b)
{
	int max_value;
	int max_value_pos;

	while (b->size > 0)
	{
		max_value = find_max_value(b);
		max_value_pos = get_index_of_value(b, max_value);
		rotate_b_to_top(b, max_value, max_value_pos);
		pa(a, b);
	}
}