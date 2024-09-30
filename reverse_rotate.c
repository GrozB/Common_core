/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:33:03 by bgroz             #+#    #+#             */
/*   Updated: 2024/09/22 10:49:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	reverse_rotate(t_stack *stack)
{
	int	bottom_value;
	int	i;

	if (stack->top < 1)
		return ;
	bottom_value = stack->array[stack->top];
	i = stack->top;
	while (i > 0)
	{
		stack->array[i] = stack->array[i - 1];
		i--;
	}
	stack->array[0] = bottom_value;
}

void	rra(t_stack *a)
{
	reverse_rotate(a);
	printf("rra\n");
}

void	rrb(t_stack *b)
{
	reverse_rotate(b);
	printf("rrb\n");
}

void	rrr(t_stack *a, t_stack *b)
{
	reverse_rotate(a);
	reverse_rotate(b);
	printf("rrr\n");
}
