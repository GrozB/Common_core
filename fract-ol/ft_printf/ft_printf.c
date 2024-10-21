/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:31:10 by bgroz             #+#    #+#             */
/*   Updated: 2024/10/07 16:33:52 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	what_is_it(const char c, va_list where)
{
	if (c == 'c')
		return (ft_putcharr(va_arg(where, int)));
	else if ((c == 'd' || c == 'i'))
		return (ft_putnbrr(va_arg(where, int)));
	else if (c == 's')
		return (ft_putstrr(va_arg(where, char *)));
	else if (c == 'x')
		return (ft_hexadec(va_arg(where, unsigned int)));
	else if (c == 'X')
		return (ft_capital_hexadec(va_arg(where, unsigned int)));
	else if (c == '%')
		return (write(1, "%", 1));
	else if (c == 'p')
		return (ft_pointer(va_arg(where, void *)));
	else if (c == 'u')
		return (ft_unsigned_dec(va_arg(where, unsigned int)));
	return (0);
}

static int	ft_loop(const char *str, va_list args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			while (str[i] == ' ' || str[i] == '\t')
				i++;
			if (str[i] == '\0')
				return (-1);
			count += what_is_it(str[i], args);
		}
		else
			count += write(1, &str[i], 1);
		i++;
	}
	return (count);
}

int	ft_printf(const char *str, ...)
{
	int		count;
	va_list	args;

	va_start(args, str);
	count = 0;
	if (str == NULL)
		return (-1);
	count += ft_loop(str, args);
	va_end(args);
	return (count);
}
/*
int main ()
{
	printf("%d",ft_printf("asd"));
	printf("%d",printf("asd"));
}
*/