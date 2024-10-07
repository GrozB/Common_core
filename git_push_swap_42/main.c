/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:24:36 by bgroz             #+#    #+#             */
/*   Updated: 2024/10/07 19:18:09 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_number(char *str)
{
	int i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	print_error_and_exit(t_stack *a, t_stack *b)
{
	write(2, "Error\n", 6);
	free_stack(a);
	free_stack(b);
	exit(1);
}

void validate_and_push(t_stack *a, t_stack *b, int argc, char **argv)
{
	int value;
	int i = argc - 1;

	
	while (i > 0)
	{
		if (!is_number(argv[i]))
		{
			print_error_and_exit(a, b);
		}
		if (!is_in_int_range(argv[i]))
		{
			print_error_and_exit(a, b);
		}
		value = ft_atoi(argv[i--]);
		if (has_duplicate(a, value))
		{
			print_error_and_exit(a, b);
		}
		push(a, value);
	}
}

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;
	int		i;

	i = argc - 1;
	if (argc <= 2 && is_number(argv[i]))
	{
		write(1, argv[1], 1);
		write(1, "\n", 1);
		return (1);	
	}
	a = stack_size(argc - 1);
	b = stack_size(argc - 1);
	if (!a || !b)
		print_error_and_exit(a, b);
	validate_and_push(a, b, argc, argv);
	if (!is_sorted(a))
	{
		simple_min_max_sort(a, b);
	}
	free_stack(a);
	free_stack(b);
	return (0);
}
