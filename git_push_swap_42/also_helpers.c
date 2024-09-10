/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   also_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:41:46 by bgroz             #+#    #+#             */
/*   Updated: 2024/07/04 14:21:03 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap_top(t_stack *swap)
{
	int	temp;

	if (swap->top < 2)
		return (0);
	temp = swap->array[swap->top];
	swap->array[swap->top] = swap->array[swap->top - 1];
	swap->array[swap->top - 1] = temp;
}

void	sa(t_stack *aswap)
{
	swap_top(aswap);
}

void	sb(t_stack *bswap)
{
	swap_top(bswap);
}

void	pa(t_stack *a, t_stack *b)
{
	int	value;

	if(!isempty(b))
	{
		pop(b, &value);
		push(a, value);
	}
}

void	pb(t_stack *a, t_stack *b)
{
	int	value;

	if(!isempty(a))
	{
		pop(a, &value);
		push(b, value);
	}
}
