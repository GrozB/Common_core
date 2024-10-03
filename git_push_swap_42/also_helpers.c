#include "push_swap.h"

void	swap_top(t_stack *swap)
{
	int	temp;

	if (swap->top < 1)
		return ;
	temp = swap->array[0];
	swap->array[0] = swap->array[1];
	swap->array[1] = temp;
}

void	sa(t_stack *aswap)
{
	swap_top(aswap);
	printf("sa\n");
}

void	sb(t_stack *bswap)
{
	swap_top(bswap);
	printf("sb\n");
}

void	pa(t_stack *a, t_stack *b)
{
	if(!is_empty(b))
	{
		push(a, b->array[0]);
		pop(b, NULL);
	}
	printf("pa\n");
}

void	pb(t_stack *a, t_stack *b)
{
	if(!is_empty(a))
	{
		push(b, a->array[0]);
		pop(a, NULL);
	}
	printf("pb\n");
}
