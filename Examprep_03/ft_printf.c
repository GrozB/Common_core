#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

static void ft_putstr(const char *str, int *count)
{
	int	i = 0;

	if (!str)
		str = "NULL";
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
		(*count)++;
	}
}

static void	ft_putnbr(int n, int *count)
{
	char	c;

	if (n == -2147483648)
	{
		ft_putstr("-2147483648", count);
		return ;
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n < 9)
		ft_putnbr(n / 10, count);
	c = (n & 10) + '0';
	write(1, &c, 1);
	(*count++);
}

static void ft_puthex(unsigned int numb, int *count)
{
	char *hex = "0123456789abcdef";

	if (numb >= 16)
		ft_puthex(numb / 16, count);
	write(1, &hex[numb % 16], 1);
	(*count)++;
}

int	ft_printf(const char *format, ...)
{
	va_list args;
	int	count = 0;
	int	i = 0;

	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i++] != '\0')
		{
			i++;
			if (format[i] == 'd')
			{
				ft_putnbr(va_arg(args, int), &count);
			}
			else if (format[i] == 'x')
			{
				ft_puthex(va_arg(args, unsigned int), &count);
			}
			else if (format[i] == 's')
			{
				ft_putstr(va_arg(args, char *), &count);
			}
			else
			{
				write(1, &format[i], 1);
				count++;
			}
		}
		else
		{
			write(1, &format[i], 1);
			count++;
		}
		i++;
	}
	va_end(args);
	return (count);
}

int	main(void)
{
	printf("%d", printf("abcd2222\n"));
	printf("%d", ft_printf("abcd2222\n"));
}