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
	stack->size = 0;
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
	int	i;

	i = stack->size;
	if (stack->top >= stack->max_size - 1)
	{
		return (-1);
	}
	stack->top++;
	while (0 < i)
	{
		stack->array[i] = stack->array[i - 1];
		i--;
	}
	stack->array[0] = value;
	stack->size++;
	return (0);
}

int pop(t_stack *stack, int *value)
{
    int i;

	if (stack->top < 0)
		return (-1);
    if (value != NULL)
        *value = stack->array[0];
    i = 0;
    while (i < stack->top)
    {
        stack->array[i] = stack->array[i + 1];
        i++;
    }
    stack->top--;
	stack->size--;
    return 0;
}

int	is_empty(t_stack *stack)
{
	if (stack->top == -1)
		return (1);
	else
		return (0);
}