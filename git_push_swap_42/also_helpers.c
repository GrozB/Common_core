/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   also_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:41:46 by bgroz             #+#    #+#             */
/*   Updated: 2024/10/07 17:29:54 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap_top(t_stack *swap)
{
	int	temp;

	if (swap->top < 1)
		return ;
	temp = swap->array[0];
	swap->array[0] = swap->array[1];
	swap->array[1] = temp;
}

void	sa(t_stack *aswap)
{
	swap_top(aswap);
	ft_printf("sa\n");
}

void	sb(t_stack *bswap)
{
	swap_top(bswap);
	ft_printf("sb\n");
}

void	pa(t_stack *a, t_stack *b)
{
	if (!is_empty(b))
	{
		push(a, b->array[0]);
		pop(b, NULL);
	}
	ft_printf("pa\n");
}

void	pb(t_stack *a, t_stack *b)
{
	int	i;

	i = b->size - 1;
	while (i >= 0)
	{
		b->array[i + 1] = b->array[i];
		i--;
	}
	b->array[0] = a->array[0];
	b->top++;
	b->size++;
	pop(a, NULL);
	ft_printf("pb\n");
}
