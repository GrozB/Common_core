#include "push_swap.h"

int	find_max_value(t_stack *stack)
{
	int i;
	int max_value;

	max_value = stack->array[0];
	i = 0;
	while (i <= stack->size)
	{
		if (stack->array[i] > max_value)
			max_value = stack->array[i];
		i++;
	}
	return (max_value);
}
/*
void push_back_to_a(t_stack *a, t_stack *b)
{
    while (b->size > 0)
    {
        int num = b->array[b->top];
        int position_in_a = find_position_in_a(a, num);
        rotate_to_top_a(a, a->array[position_in_a]);
        pa(a, b);
    }
}

int find_position_in_a(t_stack *a, int num)
{
    int position = 0;
    int i = 0;

    while (i < a->size)
    {
        if (a->array[i] > num && (i == 0 || a->array[i - 1] < num))
        {
            position = i;
            break;
        }
        i++;
    }

    return position;
}

void copy_stack_to_array(t_stack *stack, int *arr)
{
	int i;

	i = 0;
	while (i <= stack->top)
	{
		arr[i] = stack->array[i];
		i++;
	}
}*/