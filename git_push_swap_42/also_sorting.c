#include "push_swap.h"

void sort_two(t_stack *a)
{
	int top;
	int bot;

	top = a->array[a->top - 1];
	bot = a->array[a->top];
	if (top > bot)
		sa(a);
}

void sort_three(t_stack *a)
{
	int top;
	int mid;
	int bot;

	top = a->array[a->top - 2];
	mid = a->array[a->top - 1];
	bot = a->array[a->top];
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

	if (!is_sorted(a))
	{
		min_value = find_min_value(a);
		while (a->array[0] != min_value)
			ra(a);
		if (!is_sorted(a))
		{
			pb(a, b);
			min_value = find_min_value(a);
			while (a->array[0] != min_value)
				ra(a);
			if (!is_sorted(a))
			{
				pb(a, b);
				sort_three(a);
				pa(a, b);
			}
			pa(a, b);
		}
	}
}

int get_index_of_value(t_stack *stack, int value)
{
    int i;

	i = 0;
    while (i < stack->size)
    {
        if (stack->array[i] == value)
            return i;
        i++;
    }
    return (-1);
}