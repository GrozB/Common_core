/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   else.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:24:29 by bgroz             #+#    #+#             */
/*   Updated: 2024/10/07 19:00:08 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_min_value(t_stack *stack)
{
	int	i;
	int	min_value;

	i = 0;
	min_value = stack->array[0];
	while (i <= stack->top)
	{
		if (stack->array[i] < min_value)
			min_value = stack->array[i];
		i++;
	}
	return (min_value);
}

int	find_max_value(t_stack *stack)
{
	int	i;
	int	max_value;

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

int	is_sorted(t_stack *a)
{
	int	i;

	i = a->top;
	while (i > 0)
	{
		if (a->array[i] < a->array[i - 1])
			return (0);
		i--;
	}
	return (1);
}

int	find_max_position(t_stack *b, int max_value)
{
	int	i;

	i = 0;
	while (i < b->size)
	{
		if (b->array[i] == max_value)
			return (i);
		i++;
	}
	return (-1);
}

void	simple_min_max_sort(t_stack *a, t_stack *b)
{
	int	j;

	if (a->size <= 5)
	{
		sort_stack_by_size(a, b);
		return ;
	}
	if (a->size <= 100)
		j = 20;
	else
		j = 73;
	push_chunks_to_b(a, b, j);
	while (a->size > 0)
	{
		pb(a, b);
	}
	push_b_to_a(a, b);
}
