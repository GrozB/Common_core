#include "push_swap.h"

void sort_two(t_stack *a)
{
	int top = a->array[a->top - 1];
	int bot = a->array[a->top];
	if (top > bot)
		sa(a);
}

void sort_three(t_stack *a)
{
	int top = a->array[a->top - 2];
	int mid = a->array[a->top - 1];
	int bot = a->array[a->top];

	if (top > mid && mid > bot) // 3 2 1
	{
		sa(a);
		rra(a);
	}
	else if (top > mid && mid < bot && top < bot) //2 1 3
		sa(a);
	else if (top > mid && mid < bot && top > bot) //3 1 2
		ra(a);
	else if (top < mid && mid > bot && top > bot) //2 3 1
		rra(a);
	else if (top < mid && mid > bot && top < bot) //1 3 2
	{
		rra(a);
		sa(a);
	}
}

void sort_four(t_stack *a, t_stack *b)
{
	int min_value;
	//int remaining_size;

	//remaining_size = a->size;
	if (!is_sorted(a))
	{
		min_value = find_min_value(a);
		while (a->array[0] != min_value)
			ra(a);
		if (!is_sorted(a))
		{
			pb(a, b);
			sort_three(a);
			pa(a, b);
		}
	}
}

void sort_five(t_stack *a, t_stack *b)
{
	int min_value;
	//int	remaining_size = a->size;

	if (!is_sorted(a))
	{
		min_value = find_min_value(a);
		while (a->array[0] != min_value)
			ra(a);
		if (!is_sorted(a))
		{
			pb(a, b);
			//remaining_size--;
			min_value = find_min_value(a);
			while (a->array[0] != min_value)
				ra(a);
			if (!is_sorted(a))
			{
				pb(a, b);
				//remaining_size--;
				sort_three(a);
				pa(a, b);
			}
			pa(a, b);
		}
	}
}

int get_index_of_value(t_stack *stack, int value)
{
    int i = 0;  // Start from the bottom (position 0)

    while (i < stack->size)  // Loop from bottom to top
    {
        if (stack->array[i] == value)
            return i;  // Return the index of the value found
        i++;
    }
    return -1;  // Return -1 if the value is not found
}