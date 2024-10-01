#include "push_swap.h"

int find_min_value(t_stack *stack)
{
    int i = 0;
    int min_value = stack->array[0];

    while (i <= stack->top)
    {
        if (stack->array[i] < min_value)
            min_value = stack->array[i];
        i++;
    }
    return min_value;
}

int is_sorted(t_stack *a)
{
    int i = a->top;
	
    while (i > 0)
    {
        if (a->array[i] < a->array[i - 1])
            return 0;
        i--;
    }
    return 1;
}


int find_max_position(t_stack *b, int max_value)
{
    int i;

    i = 0;
    while (i < b->size)
    {
        if (b->array[i] == max_value)
            return i;
        i++;
    }
    return -1;
}

void rotate_to_top_a(t_stack *a, int value)
{
    int index = get_index_of_value(a, value);
    int half_size = a->size / 2;
    if (index < half_size)
    {
        // Rotate forward (clockwise) to bring value to the top
        while (a->array[0] != value)
            ra(a);
    }
    else
    {
        // Rotate backward (counterclockwise) to bring value to the top
        while (a->array[0] != value)
            rra(a);
    }
}

void rotate_to_top(t_stack *stack, int value)
{
    int index = get_index_of_value(stack, value);
    int half_size = stack->size / 2;

    if (index == 0)
        return;  // Already at position 0, no rotation needed

    if (index >= half_size)
    {
        while (stack->array[0] != value)
            rb(stack);  // Rotate forward
    }
    else
    {
        while (stack->array[0] != value)
            rrb(stack);  // Rotate backward
    }
}

void simple_min_max_sort(t_stack *a, t_stack *b)
{
    int k = 0;
    int l;
	int	i;
	int	size;
	int max_value;

	i = 0;
    while (k <= 5)
    {
		i = 0;
        l = find_nth_smallest(a, 20);
		while (a->array[i] != a->array[a->top])
			i++;
        while (i > 0)
        {
            if (a->array[0] <= l)
            {
                pb(a, b);
            }
            else
            {
                ra(a);
            }
			i--;
        }
		k++;
    }
	size = a->size;
	while(size > 0)
	{
		pb(a, b);
		size--;
	}
	max_value = find_max_value(b);
	printf("max value:%d", max_value);
	while (b->array[0] != max_value)
	{
		rb(b);
	}
	printf("b->array[0]:%d", b->array[0]);
	print_stack(b);
	pa(a,b);
	print_stack(b);
}
/*
void simple_min_max_sort(t_stack *a, t_stack *b)
{
    int min_rotations;
    int max_rotations;
    int next_min_rotations;
	int abs_min_rotations;
	int abs_max_rotations;
	int abs_next_min_rotations;
    int next_min_values_count = 0;
    int counter = 0;
    int i = 0;
	int sign = 0;

    while (a->size > 0)
    {
        int min_value = find_min_value(a);
        int max_value = find_max_value(a);
        int next_min_value = find_next_min_value(a);
        min_rotations = calculate_rotations(get_index_of_value(a, min_value), a->size);
        max_rotations = calculate_rotations(get_index_of_value(a, max_value), a->size);
        next_min_rotations = calculate_rotations(get_index_of_value(a, next_min_value), a->size);
		abs_min_rotations = abs(min_rotations);
		abs_max_rotations = abs(max_rotations);
		abs_next_min_rotations = abs(next_min_rotations);

		//print_stack(a);
		if (is_sorted(a) && next_min_values_count == 0)
			break;
        if (abs_min_rotations <= abs_max_rotations && abs_min_rotations <= abs_next_min_rotations)
        {
			//printf("min_rotations is called: %d max_value: %d, min_value: %d, next_min_value: %d\n", min_rotations, max_value, min_value, next_min_value);
            rotate_to_top_a(a, min_value);
            i = next_min_values_count;
			if (next_min_values_count == 1)
			{
				pb(a, b);
				sb(b);
				next_min_values_count--;
				i--;
				sign = 1;
			}
            while (next_min_values_count > 0)
            {
                rb(b);
                next_min_values_count--;
            }
			if (sign == 0)
            	pb(a, b);
            while (i > 0)
            {
                rrb(b);
                i--;
            }
			sign = 0;
        }
        else if (abs_max_rotations <= abs_next_min_rotations && abs_max_rotations < abs_min_rotations)
        {
			//printf("max_rotations is called: %d max_value: %d, min_value: %d, next_min_value: %d\n", max_rotations, max_value, min_value, next_min_value);
            rotate_to_top_a(a, max_value);
            pb(a, b);
            rb(b);
            counter++;
        }
        else
        {
			//printf("next_min_rotations is called: %d max_value: %d, min_value: %d, next_min_value: %d\n", next_min_rotations, max_value, min_value, next_min_value);
            rotate_to_top_a(a, next_min_value);
            pb(a, b);
            next_min_values_count++;
        }
    }
    while (b->size > 0)
    {
        pa(a, b);
    }
    while (counter > 0)
    {
        ra(a);
        counter--;
    }
}*/
/*
void simple_min_max_sort(t_stack *a, t_stack *b)
{
    int min_rotations;
    int max_rotations;
	int	min_value;
	int	max_value;
	int	next_max_value;
    //int next_min_rotations;
	int	next_max_rotations;
	int	median = find_median(a);
	int original_size = a->size;
	int abs_min_rotations;
	int abs_max_rotations;
	int abs_next_max_rotations;
    //make int next_min_values_count = 0;
	int next_max_values_count = 0;
    int counter = 0;
    int i = 0;

    while (original_size > 0)
	{
		if (a->array[0] > median)
		{
			pb(a, b);
			//printf("Stack B (size %d):\n", b->size);
		}
		else
		{
			rra(a);  // Rotate stack_a
		}
		original_size--;
	}

	while (!is_empty(a))
	{
        min_value = find_min_value(a);
        max_value = find_max_value(a);
        next_max_value = find_next_max_value(a);
        min_rotations = calculate_rotations(get_index_of_value(a, min_value), a->size);
        max_rotations = calculate_rotations(get_index_of_value(a, max_value), a->size);
        next_max_rotations = calculate_rotations(get_index_of_value(a, next_max_value), a->size);
		abs_min_rotations = abs(min_rotations);
		abs_max_rotations = abs(max_rotations);
		abs_next_max_rotations = abs(next_max_rotations);


		//printf("min_value: %d, min_index: %d, min_rotations: %d\n", min_value, get_index_of_value(b, min_value), min_rotations);
		//printf("max_value: %d, max_index: %d, max_rotations: %d\n", max_value, get_index_of_value(b, max_value), max_rotations);
		//printf("next_max_value: %d, next_max_index: %d, next_max_rotations: %d\n", next_max_value, get_index_of_value(b, next_max_value), next_max_rotations);
		//break;
		//print_stack(b);
		//print_stack(a);
        if (abs_max_rotations <= abs_min_rotations && abs_max_rotations <= abs_next_max_rotations)
        {
			//printf("max_rotations is called: %d max_value: %d, min_value: %d, next_max_value: %d\n", max_rotations, max_value, min_value, next_max_value);
            rotate_to_top(a, max_value);
			//print_stack(b);
            i = next_max_values_count;
            while (next_max_values_count > 0)
            {
                ra(a);
                next_max_values_count--;
            }
            pb(a, b);
            while (i > 0)
            {
                rra(a);
                i--;
            }
        }
        else if (abs_min_rotations < abs_next_max_rotations && abs_min_rotations < abs_max_rotations)
        {
			//printf("min_rotations is called: %d max_value: %d, min_value: %d, next_max_value: %d\n", min_rotations, max_value, min_value, next_max_value);
			//printf("stack before rotate to top b:");
            rotate_to_top(a, min_value);
			//print_stack(b);
            pb(a, b);
            rb(b);
            counter++;
        }
        else if (abs_next_max_rotations <= abs_max_rotations && abs_next_max_rotations <= abs_min_rotations)
        {
			//printf("next_max_rotations is called: %d max_value: %d, min_value: %d, next_max_value: %d\n", next_max_rotations, max_value, min_value, next_max_value);
            rotate_to_top(a, next_max_value);
			//print_stack(b);
            pb(a, b);
            next_max_values_count++;
        }
    }
    while (b->size > 0)
    {
        pa(a, b);
    }
    while (counter > 0)
    {
        rra(a);
        counter--;
    }
}
*/
//working push swap with 960 avg moves
/*
void simple_min_max_sort(t_stack *a, t_stack *b)
{
    int min_rotations;
    int max_rotations;
    int next_min_rotations;
	int abs_min_rotations;
	int abs_max_rotations;
	int abs_next_min_rotations;
    int next_min_values_count = 0;
    int counter = 0;
    int i = 0;

    while (a->size > 0)
    {
        int min_value = find_min_value(a);
        int max_value = find_max_value(a);
        int next_min_value = find_next_min_value(a);
        min_rotations = calculate_rotations(get_index_of_value(a, min_value), a->size);
        max_rotations = calculate_rotations(get_index_of_value(a, max_value), a->size);
        next_min_rotations = calculate_rotations(get_index_of_value(a, next_min_value), a->size);
		abs_min_rotations = abs(min_rotations);
		abs_max_rotations = abs(max_rotations);
		abs_next_min_rotations = abs(next_min_rotations);

		//print_stack(a);
        if (abs_min_rotations <= abs_max_rotations && abs_min_rotations <= abs_next_min_rotations)
        {
			//printf("min_rotations is called: %d max_value: %d, min_value: %d, next_min_value: %d\n", min_rotations, max_value, min_value, next_min_value);
            rotate_to_top_a(a, min_value);
            i = next_min_values_count;
            while (next_min_values_count > 0)
            {
                rb(b);
                next_min_values_count--;
            }
            pb(a, b);
            while (i > 0)
            {
                rrb(b);
                i--;
            }
        }
        else if (abs_max_rotations <= abs_next_min_rotations && abs_max_rotations < abs_min_rotations)
        {
			//printf("max_rotations is called: %d max_value: %d, min_value: %d, next_min_value: %d\n", max_rotations, max_value, min_value, next_min_value);
            rotate_to_top_a(a, max_value);
            pb(a, b);
            rb(b);
            counter++;
        }
        else
        {
			//printf("next_min_rotations is called: %d max_value: %d, min_value: %d, next_min_value: %d\n", next_min_rotations, max_value, min_value, next_min_value);
            rotate_to_top_a(a, next_min_value);
            pb(a, b);
            next_min_values_count++;
        }
    }
    while (b->size > 0)
    {
        pa(a, b);
    }
    while (counter > 0)
    {
        ra(a);
        counter--;
    }
}*/