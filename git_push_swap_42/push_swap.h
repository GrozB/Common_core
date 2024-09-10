/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:14:40 by bgroz             #+#    #+#             */
/*   Updated: 2024/07/04 13:40:51 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <stdlib.h>
# include "libft/libft.h"

typedef struct s_stack
{
	int	*array;
	int	top;
	int	size;
	int	max_size;
}	t_stack;

t_stack	*stack_size(int size);
void	free_stack(t_stack *stack);
int	push(t_stack *stack, int value);
int	pop(t_stack *stack, int *value);
int	is_empty(t_stack *stack);

#endif
