/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lonely.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:55:07 by bgroz             #+#    #+#             */
/*   Updated: 2024/10/10 19:55:20 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void initialize_stack_size(t_stack **a, t_stack **b, int size)
{
	*a = stack_size(size);
	*b = stack_size(size);
	if (!(*a) || !(*b))
		print_error_and_exit(*a, *b);
}
