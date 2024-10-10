/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:25:08 by bgroz             #+#    #+#             */
/*   Updated: 2024/10/10 19:20:17 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_chunk(t_stack *a, t_stack *b, int limit, int i)
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

void	push_chunks_to_b(t_stack *a, t_stack *b, int chunk_size)
{
	int	k;
	int	limit;

	k = 0;
	while (k <= 5)
	{
		limit = find_nth_smallest(a, chunk_size);
		push_chunk(a, b, limit, a->size);
		k++;
	}
}

void	push_b_to_a(t_stack *a, t_stack *b)
{
	int	max_value;
	int	max_value_pos;

	while (b->size > 0)
	{
		max_value = find_max_value(b);
		max_value_pos = get_index_of_value(b, max_value);
		rotate_b_to_top(b, max_value, max_value_pos);
		pa(a, b);
	}
}

int	has_duplicate(t_stack *stack, int value)
{
	int	i;

	i = 0;
	while (i < stack->size)
	{
		if (stack->array[i] == value)
			return (1);
		i++;
	}
	return (0);
}

int	is_in_int_range(const char *str)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		result = result * 10 + (*str - '0');
		if ((sign == 1 && result > INT_MAX)
			|| (sign == -1 && (-result) < INT_MIN))
			return (0);
		str++;
	}
	return (1);
}
