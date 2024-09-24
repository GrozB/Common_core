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

void calculate_thresholds(int *arr, int *thresholds, int size, int num_chunks)
{
    int i = 0;
    int chunk_size = size / num_chunks;

    while (i < num_chunks - 1)
    {
        thresholds[i] = arr[chunk_size * (i + 1) - 1];
        i++;
    }
    thresholds[num_chunks - 1] = arr[size - 1];
}

int	find_max_value(t_stack *stack)
{
	int i;
	int max_value;

	max_value = stack->array[stack->top];
	i = stack->top - 1;
	while (i >= 0)
	{
		if (stack->array[i] > max_value)
			max_value = stack->array[i];
		i--;
	}
	return (max_value);
}

void push_chunks_to_b(t_stack *a, t_stack *b, int chunk_size)
{
	int min;
	int max;
	int i;
	int chunk_count = 0;

	while (a->size > 0)
	{
		min = chunk_count * chunk_size;
		max = (chunk_count + 1) * chunk_size;
		i = 0;
		while (i < a->size)
		{
			if (a->array[0] >= min && a->array[0] <= max)
				pb(a, b);
			else
				ra(a);
			i++;
		}
		chunk_count++;
	}
}

void push_back_to_a(t_stack *a, t_stack *b)
{
	int max_value;

	while (!is_empty(b))
	{
		max_value = find_max_value(b);
		while (b->array[b->top] != max_value)
		{
			if (find_max_position(b, max_value) <= b->size / 2)
				rb(b);
			else
				rrb(b);
		}
		//printf("debugging");
		pa(a, b);
	}
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
