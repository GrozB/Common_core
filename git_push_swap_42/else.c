/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:43:00 by marvin            #+#    #+#             */
/*   Updated: 2024/09/18 19:43:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int find_min_value(t_stack *stack)
{
    int i;
    int min_value;

    min_value = stack->array[stack->top];
    i = stack->top - 1;
    while (i >= 0)
    {
        if (stack->array[i] < min_value)
            min_value = stack->array[i];
        i--;
    }
    return min_value;
}

int is_sorted(t_stack *a)
{
    int i = a->top;
	
    while (i > 0)
    {
        if (a->array[i] < a->array[i - 1])
            return 0;
        i--;
    }
    return 1;
}


int find_max_position(t_stack *b, int max_value)
{
    int i;

    i = 0;
    while (i < b->size)
    {
        if (b->array[i] == max_value)
            return i;
        i++;
    }
    return -1;
}

void rotate_to_top(t_stack *a, int value)
{
    int half_size = a->size / 2;
    int index = get_index_of_value(a, value);

    if (index <= half_size)
    {
        while (a->array[0] != value)
            ra(a);
    }
    else
    {
        while (a->array[0] != value)
            rra(a);
    }
}

void simple_min_max_sort(t_stack *a, t_stack *b)
{
    int min_value;
    int max_value;
    int min_index;
    int max_index;
	int counter;

	counter = 0;
    while (a->size > 5)
    {
        min_value = find_min_value(a);
        max_value = find_max_value(a);
        min_index = get_index_of_value(a, min_value);
        max_index = get_index_of_value(a, max_value);
        if (min_index <= max_index)
        {
            rotate_to_top(a, min_value);
            pb(a, b);
        }
        else
        {
            rotate_to_top(a, max_value);
            pb(a, b);
			rb(b);
			counter++;
        }
    }
    sort_stack_by_size(a, b);
	min_value = find_min_value(a);
    while (b->size > 0)
	{
        pa(a, b);
	}
	while (counter > 0)
	{
		ra(a);
		counter--;
	}
}