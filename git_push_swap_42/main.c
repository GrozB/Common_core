/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:24:36 by bgroz             #+#    #+#             */
/*   Updated: 2024/10/10 19:33:24 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			i++;
			continue ;
		}
		if ((str[i] == '-' || str[i] == '+') && (i == 0 || str[i - 1] == ' ')
			&& str[i + 1] >= '0' && str[i + 1] <= '9')
			i++;
		else if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (0);
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

void	free_split(char **split_args)
{
	int	i;

	i = 0;
	while (split_args[i])
	{
		free(split_args[i]);
		i++;
	}
	free(split_args);
}

void	validate_and_push(t_stack *a, t_stack *b, int argc, char **argv)
{
	int	value;
	int	i;
	int	counter;

	counter = 0;
	i = argc - 1;
	while (i > 0)
	{
		if (!is_number(argv[i]) || !is_in_int_range(argv[i]))
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

	if (argc < 2)
		return (1);
	initialize_stacks(&a, &b, argc, argv);
	if (!is_sorted(a))
		simple_min_max_sort(a, b);
	free_stack(a);
	free_stack(b);
	return (0);
}
