/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:30:34 by bgroz             #+#    #+#             */
/*   Updated: 2024/07/04 11:27:06 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*stack_size(int size)
{
	t_stack	*stack;

	stack = (t_stack *)malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->array = (int *)malloc(sizeof(int) * size);
	if (!stack->array)
	{
		free (stack);
		return (NULL);
	}
	stack->top = -1;
	stack->max_size = size;
	return (stack);
}

void	free_stack(t_stack *stack)
{
	if (stack)
	{
		free(stack->array);
		free(stack);
	}
}

int	push(t_stack *stack, int value)
{
	if (stack->top >= stack->max_size - 1)
		return (-1);
	stack->top++;
	stack->array[stack->top] = value;
	stack->size++;
	return (0);
}

int	pop(t_stack *stack, int *value)
{
	if (stack->top == -1)
		return (-1);
	*value = stack->array[stack->top];
	stack->top--;
	stack->size--;
	return (0);
}

int	is_empty(t_stack *stack)
{
	if (stack->top == -1)
		return (1);
	else
		return (0);
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		ft_printf("Usage: %s <list of integers>\n", argv[0]);
		return 1;
	}
	t_stack *stack = stack_size(argc - 1);
	if (!stack)
	{
		ft_printf("Failed to create stack\n");
		return 1;
	}
	for (int i = 1; i < argc; i++)
	{
		int value = ft_atoi(argv[i]);
		if (push(stack, value) == 0)
			ft_printf("Pushed %d\n", value);
		else
		{
			ft_printf("Failed to push %d\n", value);
			free_stack(stack);
			return 1;
		}
	}
	int value;
	while (!is_empty(stack))
	{
		if (pop(stack, &value) == 0)
			ft_printf("Popped value: %d\n", value);
		else
			ft_printf("Failed to pop\n");
	}
	if (is_empty(stack))
		ft_printf("Stack is empty\n");
	else
		ft_printf("Stack is not empty\n");

	free_stack(stack);

	return 0;
}
