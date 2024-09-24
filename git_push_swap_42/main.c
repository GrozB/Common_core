/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:43:13 by marvin            #+#    #+#             */
/*   Updated: 2024/09/13 15:43:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;
	int		i;
	int		value;

	if (argc <= 2)
		return (1);
	a = stack_size(argc - 1);
	b = stack_size(argc - 1);
	if (!a || !b)
		return (free_stack(a), free_stack(b), 1);
	i = 1;
	while (i < argc)
	{
		value = ft_atoi(argv[i++]);
		push(a, value);
	}
	if (!is_sorted(a))
	{
		simple_min_max_sort(a, b);
		free_stack(a);
		free_stack(b);
	}
	return (0);
}
