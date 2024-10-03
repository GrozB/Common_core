#include "push_swap.h"

void sort_stack_by_size(t_stack *a, t_stack *b)
{
    if (a->size == 2)
        sort_two(a);
    else if (a->size == 3)
        sort_three(a);
    else if (a->size == 4)
        sort_four(a, b);
    else if (a->size == 5)
        sort_five(a, b);
}

int calculate_rotations(int index, int size)
{
    int rotations;

    if (index <= size / 2)
    {
        rotations = index;
    }
    else
    {
        rotations = -(size - index);
    }
    return rotations;
}

int find_next_min_value(t_stack *stack)
{
    int first_min_value = find_min_value(stack);
    int i = stack->top;
    int next_min_value = stack->array[stack->top];

    while (i >= 0)
    {
        if (stack->array[i] > first_min_value && stack->array[i] < next_min_value)
        {
            next_min_value = stack->array[i];
        }
        i--;
    }

    return next_min_value;
}

int find_next_max_value(t_stack *stack)
{
    int first_max_value = find_max_value(stack);

    int i = stack->top;
    int next_max_value = stack->array[stack->top];
    while (i >= 0)
    {
        if (stack->array[i] < first_max_value && stack->array[i] > next_max_value)
        {
            next_max_value = stack->array[i];
        }
        i--;
    }
    return next_max_value;
}

void bubble_sort_rec(int *arr, int n)
{
    if (n == 1)
        return;

    int i = 0;
    while (i < n - 1)
    {
        if (arr[i] > arr[i + 1])
        {
            int temp = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = temp;
        }
        i++;
    }
    bubble_sort_rec(arr, n - 1);
}

int find_median(t_stack *a)
{
    int sorted[a->size];
    int i = 0;
	
    while (i < a->size)
    {
        sorted[i] = a->array[i];
        i++;
    }
    bubble_sort_rec(sorted, a->size);
    return sorted[a->size / 2];
}

void print_stack(t_stack *stack)
{
    int i = 0;

    printf("Stack (size %d): ", stack->size);
    while (i < stack->size)
    {
        printf("%d ", stack->array[i]);
        i++;
    }
    printf("\n");
}

int calculate_position_in_a(t_stack *a, int value)
{
    int i = 0;

    {
        if (a->array[i] > value)
            return i;
        i++;
    }
    return 0;
}

void rotate_to_position_a(t_stack *a, int position)
{
    int half_size = a->size / 2;

    if (position <= half_size)
    {
        {
            ra(a);
            position--;
        }
    }
    else
    {
        while (position < a->size)
        {
            rra(a);
            position++;
        }
    }
}

int find_nth_smallest(t_stack *a, int n)
{
    int i;
    int j = 0;
    int current_smallest;
    int nth_smallest = find_min_value(a);

    while (j < n - 1)
    {
        current_smallest = find_max_value(a);
        i = 0;
        while (i <= a->size)
        {
            if (a->array[i] > nth_smallest && a->array[i] < current_smallest)
                current_smallest = a->array[i];
            i++;
        }
        nth_smallest = current_smallest;
        j++;
    }
    return nth_smallest;
}
