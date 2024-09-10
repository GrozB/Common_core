/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:33:03 by bgroz             #+#    #+#             */
/*   Updated: 2024/08/28 18:45:36 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	reverse_rotate(t_stack *stack)
{
	int	bottom_value;
	int	i;

	if (stack-> < 1)
		return ;
	bottom_value = stack->array[0];
	i = 0;
	while (i <  stack->top)
	{
		stack->array[i] = stack->array[i + 1];
		i++;
	}
	stack->array[stack->top] = bottom_value;
}

void	rra(t_stack *a)
{
	reverse_rotate(a);
}

void	rrb(t_stack *b)
{
	reverse_rotate(b);
}

void	rrr(t_stack *a, t_stack *b)
{
	reverse_rotate(a);
	reverse_rotate(b);
}