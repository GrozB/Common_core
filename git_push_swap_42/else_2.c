/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   else_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:24:27 by bgroz             #+#    #+#             */
/*   Updated: 2024/10/10 19:53:32 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_stack_by_size(t_stack *a, t_stack *b)
{
	if (a->size == 1)
		return ;
	if (a->size == 2)
		sort_two(a);
	else if (a->size == 3)
		sort_three(a);
	else if (a->size == 4)
		sort_four(a, b);
	else if (a->size == 5)
		sort_five(a, b);
}

int	calculate_rotations(int index, int size)
{
	int	rotations;

	if (index <= size / 2)
	{
		rotations = index;
	}
	else
	{
		rotations = -(size - index);
	}
	return (rotations);
}

int	find_nth_smallest(t_stack *a, int n)
{
	int	i;
	int	j;
	int	current_smallest;
	int	nth_smallest;

	j = 0;
	nth_smallest = find_min_value(a);
	while (j < n - 1)
	{
		current_smallest = find_max_value(a);
		i = 0;
		while (i < a->size)
		{
			if (a->array[i] > nth_smallest
				&& a->array[i] < current_smallest)
				current_smallest = a->array[i];
			i++;
		}
		nth_smallest = current_smallest;
		j++;
	}
	return (nth_smallest);
}

void	initialize_stacks(t_stack **a, t_stack **b, int argc, char **argv)
{
	char	**values;
	int		size;

	if (argc == 2 && is_number(argv[1]))
	{
		values = ft_split(argv[1], ' ');
		if (!values)
			print_error_and_exit(*a, *b);
		size = 0;
		while (values[size])
			size++;
		initialize_stack_size(a, b, size);
		process_values(*a, *b, values);
		free_split(values);
	}
	else
	{
		initialize_stack_size(a, b, argc - 1);
		process_values(*a, *b, &argv[1]);
	}
}

void	process_values(t_stack *a, t_stack *b, char **values)
{
	int	i;

	i = 0;
	while (values[i])
	{
		if (!is_in_int_range(values[i]) || has_duplicate(a, ft_atoi(values[i])))
			print_error_and_exit(a, b);
		a->array[i] = ft_atoi(values[i]);
		i++;
		a->size++;
	}
	a->top = i - 1;
}
